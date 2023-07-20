package com.test.lotproject;

import android.Manifest;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Bundle;

import com.google.android.material.tabs.TabLayout;
import com.huaweicloud.sdk.iot.device.IoTDevice;
import com.huaweicloud.sdk.iot.device.client.requests.DeviceMessage;
import com.huaweicloud.sdk.iot.device.client.requests.ServiceProperty;
import com.huaweicloud.sdk.iot.device.constant.IotDeviceIntent;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;
import androidx.viewpager.widget.ViewPager;



public class MainActivity extends AppCompatActivity {
    private ViewPager vp_main;
    private TabLayout tab_main;
    private List<Fragment> mFragments;
    private ConnectBroadcastReceiver connectBroadcastReceiver;
    private String serverUri = "ssl://21b6fca8fe.st1.iotda-device.cn-east-3.myhuaweicloud.com:8883";
    public String deviceId = "63f5b8324db8e021b6229e14_12336556656564";
    private String deviceSecret = "12345678";
    private IoTDevice device;
    public static String requestId="888";

    //模拟数据： {"type":1,"name":"小香风外套女","price":"799.00","pic":"https://g-search3.alicdn.com/img/bao/uploaded/i4/i3/356060330/O1CN01kE0f5V1EJBVtzBFYi-356060330.jpg"}
    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        vp_main = findViewById(R.id.vp_main);
        tab_main = findViewById(R.id.tab_main);
        initPermission();
        initTabLayout();
        initMqtt();
    }

    private void initMqtt() {
        connectBroadcastReceiver = new ConnectBroadcastReceiver();
        device = new IoTDevice(this, serverUri, deviceId, deviceSecret);
        //连接的广播
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_CONNECT));
        //属性上报的广播
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_PROPERTIES_REPORT));
        //消息上报的广播
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_SYS_MESSAGES_UP));
        //平台查询设备属性广播
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_SYS_PROPERTIES_GET));
        //平台设置设备属性广播
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_SYS_PROPERTIES_SET));
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_SYS_SHADOW_GET));
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_SYS_COMMANDS));
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_CUSTOMIZED_TOPIC_CONNECT));
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_CUSTOMIZED_TOPIC_MESSAGE));
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_CUSTOMIZED_TOPIC_REPORT));

        //        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver,new  IntentFilter(Constant.SMOKE_DETECTOR_PROPERTY));
        //        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver,new  IntentFilter(Constant.SMOKE_DETECTOR_COMMAND));
        //        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver,new  IntentFilter(Constant.SMOKE_SHADOW_ACTION));
        //        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver,new  IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_TIME_SYNC_RESPONSE));
        //        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver,new  IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_BOOTSTRAP_REQUEST_TRIGGER));
        //        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver,new  IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_BOOTSTRAP));

        //接收下发消息的广播
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_SYS_MESSAGES_DOWN));
        //
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_PROPERTIES_REPORT_V3));
        LocalBroadcastManager.getInstance(this).registerReceiver(connectBroadcastReceiver, new IntentFilter(IotDeviceIntent.ACTION_IOT_DEVICE_SYS_COMMANDS_V3));
        device.init();

        //$oc/devices/{device_id}/sys/properties/report
        device.getClient().subscribeTopicV3("$oc/devices/"+ deviceId +"/sys/commands/"+"f58c939e-8bc3-4c73-8cc5-1a59a82f2e59",0);
    }

    /**
     * 上报属性
     */
    public void uploadPro(ServiceProperty property) {
        //创建属性
        List<ServiceProperty> serviceProperties = new ArrayList<>();
        serviceProperties.add(property);
        //上报属性
        device.getClient().reportProperties(serviceProperties);

    }

    /**
     * 上报消息
     */
    public void uploadMesg(DeviceMessage deviceMessage) {
        device.getClient().reportDeviceMessage(deviceMessage);
    }

//    /**
//     *  获取设备属性
//     * @param serviceId     设备的服务ID
//     * @param propertyKey   设备的属性
//     * @param propertyValue 设备的属性值
//     * @return
//     */
   public void getProperties(String serviceId,String propertyKey,String propertyValue){
        List<ServiceProperty> serviceProperties = getServiceProperties(serviceId,propertyKey,propertyValue);
        device.getClient().respondPropsGet(requestId, serviceProperties);

    }

    public void getShadowData(){
        device.getClient().subscribeTopic("test1", 0);
    }

    private void initTabLayout() {
        mFragments = new ArrayList<>();
        //mFragments.add(new MainFragment());
        mFragments.add(new FoodFragment());
        mFragments.add(new PayFragment());
        mFragments.add(new CodeFragment());
        TabViewPagerAdapter adapter = new TabViewPagerAdapter(getSupportFragmentManager(), mFragments);
        vp_main.setAdapter(adapter);
        vp_main.setOffscreenPageLimit(3);
        tab_main.setupWithViewPager(vp_main);
        //tab_main.getTabAt(0).setText("首页");
        tab_main.getTabAt(0).setText("购物车");
        tab_main.getTabAt(1).setText("结算");
        tab_main.getTabAt(2).setText("二维码");
    }

    private void initPermission() {
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{
                    Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.ACCESS_NETWORK_STATE,
                    Manifest.permission.ACCESS_WIFI_STATE, Manifest.permission.WAKE_LOCK,
                    Manifest.permission.EXPAND_STATUS_BAR
            }, 123);
        }
    }

    /**
     * @param serviceId     设备的服务ID
     * @param propertyKey   设备的属性
     * @param propertyValue 设备的属性值
     * @return
     */
    private List<ServiceProperty> getServiceProperties(String serviceId,String propertyKey,String propertyValue) {
        Map<String, Object> properties = new HashMap<String, Object>();
        properties.put(propertyKey, propertyValue);
        ServiceProperty serviceProperty = new ServiceProperty();
        serviceProperty.setServiceId(serviceId);
        serviceProperty.setProperties(properties);
        List<ServiceProperty> serviceProperties = new ArrayList<ServiceProperty>();
        serviceProperties.add(serviceProperty);
        return serviceProperties;
    }

}
