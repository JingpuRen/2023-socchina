package com.test.lotproject;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.google.gson.Gson;
import com.huaweicloud.sdk.iot.device.client.requests.Command;
import com.huaweicloud.sdk.iot.device.client.requests.DeviceMessage;
import com.huaweicloud.sdk.iot.device.client.requests.PropsSet;
import com.huaweicloud.sdk.iot.device.client.requests.ShadowMessage;
import com.huaweicloud.sdk.iot.device.constant.BaseConstant;
import com.huaweicloud.sdk.iot.device.constant.IotDeviceIntent;
import com.huaweicloud.sdk.iot.device.transport.RawMessage;

import org.greenrobot.eventbus.EventBus;

import java.io.UnsupportedEncodingException;

import static com.huaweicloud.sdk.iot.device.constant.BaseConstant.PROPERTIES_REPORT_ERROR;


public class ConnectBroadcastReceiver extends BroadcastReceiver {

    String TAG = "hao";

    @Override
    public void onReceive(Context context, Intent intent) {
        Log.e(TAG, "onReceive: " + intent.getAction());

        if (IotDeviceIntent.ACTION_IOT_DEVICE_CONNECT.equals(intent.getAction())) {
            int broadcastStatus = intent.getIntExtra(BaseConstant.BROADCAST_STATUS, BaseConstant.STATUS_FAIL);
            switch (broadcastStatus) {
                case BaseConstant.STATUS_SUCCESS:
                    Log.e("hao", "设备创建成功!");
                    break;
                case BaseConstant.STATUS_FAIL:
                    //提示连接异常
                    String error = intent.getStringExtra(BaseConstant.COMMON_ERROR);
                    Log.e("hao", "设备创建失败!失败原因：" + error + "\n");
                    break;
                default:
                    Log.i(TAG, "onReceive: broadcastStatus=" + broadcastStatus);
                    break;
            }
        } else if (IotDeviceIntent.ACTION_IOT_DEVICE_SYS_MESSAGES_DOWN.equals(intent.getAction())) {
            //接收消息
            DeviceMessage deviceMessage = intent.getParcelableExtra(BaseConstant.SYS_DOWN_MESSAGES);
            String content = deviceMessage.getContent();
            try {
                FoodBean bean = new Gson().fromJson(content, FoodBean.class);
                if (bean != null) {
                    EventBus.getDefault().post(bean);
                }
            }catch (Exception e){
                Log.e("hao", e.toString());
            }

        }else if (IotDeviceIntent.ACTION_IOT_DEVICE_PROPERTIES_REPORT.equals(intent.getAction())){
            int broadcastStatus = intent.getIntExtra(BaseConstant.BROADCAST_STATUS, BaseConstant.STATUS_FAIL);
            switch (broadcastStatus) {
                case BaseConstant.STATUS_SUCCESS:
                    Log.e("hao","上报属性成功!");
                    break;
                case BaseConstant.STATUS_FAIL:
                    String error = intent.getStringExtra(PROPERTIES_REPORT_ERROR);
                    Log.e("hao","上报属性失败!失败原因：" + error);
                    break;
            }
        }else if (IotDeviceIntent.ACTION_IOT_DEVICE_SYS_MESSAGES_UP.equals(intent.getAction())){
            int broadcastStatus = intent.getIntExtra(BaseConstant.BROADCAST_STATUS, BaseConstant.STATUS_FAIL);
            switch (broadcastStatus) {
                case BaseConstant.STATUS_SUCCESS:
                    Log.e("hao","上报消息成功!");
                    break;
                case BaseConstant.STATUS_FAIL:
                    String error = intent.getStringExtra(PROPERTIES_REPORT_ERROR);
                    Log.e("hao","上报消息失败!失败原因：" + error);
                    break;
            }
        }else if (IotDeviceIntent.ACTION_IOT_DEVICE_SYS_PROPERTIES_GET.equals(intent.getAction())){
            //平台查询设备属性广播携带数据
           MainActivity.requestId = intent.getStringExtra(BaseConstant.REQUEST_ID);
            String serviceId = intent.getStringExtra(BaseConstant.SERVICE_ID);
            Log.e("hao","平台查询设备属性: " + "requestId=" + MainActivity.requestId + ",serviceId=" + serviceId);
        }else if (IotDeviceIntent.ACTION_IOT_DEVICE_SYS_PROPERTIES_SET.equals(intent.getAction())){
            //平台设置设备属性广播携带数据
            MainActivity.requestId = intent.getStringExtra(BaseConstant.REQUEST_ID);
            PropsSet propsSet = intent.getParcelableExtra(BaseConstant.SYS_PROPERTIES_SET);

            Log.e("hao","平台查询设备属性: " + "requestId=" + MainActivity.requestId + ",propsSet=" + propsSet.toString());
        }else if (IotDeviceIntent.ACTION_IOT_DEVICE_SYS_SHADOW_GET.equals(intent.getAction())){

            MainActivity.requestId = intent.getStringExtra(BaseConstant.REQUEST_ID);
            ShadowMessage shadowMessage = intent.getParcelableExtra(BaseConstant.SHADOW_DATA);

            Log.e("hao","影子数据: " + "requestId=" + MainActivity.requestId + ",shadowMessage=" + shadowMessage.toString());
        }else if (IotDeviceIntent.ACTION_IOT_DEVICE_SYS_COMMANDS.equals(intent.getAction())){

            MainActivity.requestId   = intent.getStringExtra(BaseConstant.REQUEST_ID);
            Command command = intent.getParcelableExtra(BaseConstant.SYS_COMMANDS);

            Log.e("hao","命令数据: " + "requestId=" + MainActivity.requestId + ",command=" + command.toString());
        }if (IotDeviceIntent.ACTION_IOT_DEVICE_CUSTOMIZED_TOPIC_CONNECT.equals(intent.getAction())) {
            int status = intent.getIntExtra(BaseConstant.BROADCAST_STATUS, BaseConstant.STATUS_FAIL);
            String topicName = intent.getStringExtra(BaseConstant.CUSTOMIZED_TOPIC_NAME);
            switch (status) {
                case BaseConstant.STATUS_SUCCESS:
                    Log.e("hao","订阅Topic成功：" + topicName + "\n");
                    break;
                case BaseConstant.STATUS_FAIL:
                    String errorMessage = intent.getStringExtra(BaseConstant.COMMON_ERROR);
                    Log.e("hao","订阅Topic失败：" + topicName + "\n");
                    Log.e("hao","失败原因：" + errorMessage + "\n");
                    break;
                default:
                    break;
            }
        } else if (IotDeviceIntent.ACTION_IOT_DEVICE_CUSTOMIZED_TOPIC_MESSAGE.equals(intent.getAction())) {
            String topicName = intent.getStringExtra(BaseConstant.CUSTOMIZED_TOPIC_NAME);
            RawMessage rawMessage = intent.getParcelableExtra(BaseConstant.CUSTOMIZED_TOPIC_MESSAGE);
            Log.e("hao","订阅Topic下发消息：" + topicName + "\n");
            try {
                Log.e("hao","下发消息内容：" + new String(rawMessage.getPayload(), "UTF-8") + "\n");
            } catch (UnsupportedEncodingException e) {
                e.printStackTrace();
            }

        }
    }
}
