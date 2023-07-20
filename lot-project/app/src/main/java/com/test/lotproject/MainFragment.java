package com.test.lotproject;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.huaweicloud.sdk.iot.device.client.requests.DeviceMessage;
import com.huaweicloud.sdk.iot.device.client.requests.ServiceProperty;

import java.util.HashMap;
import java.util.Map;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;


public class MainFragment extends Fragment {

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_home, container, false);
        initView(view);
        return view;
    }

    private void initView(View view) {
        final MainActivity activity = (MainActivity) getActivity();
        view.findViewById(R.id.tv).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                DeviceMessage message = new DeviceMessage();
                message.setDeviceId(activity.deviceId);
                message.setId(activity.deviceId);
                message.setName("测试用");
                message.setContent("{\n" +
                        "  \"resource\": \"device.message\",\n" +
                        "  \"event\": \"report\",\n" +
                        "  \"event_time\": \"string\",\n" +
                        "  \"notify_data\": {\n" +
                        "    \"header\": {\n" +
                        "      \"app_id\": \"63f5b8324db8e021b6229e14_12336556656564\",\n" +
                        "      \"device_id\": \"63f5b8324db8e021b6229e14_mqttfx\",\n" +
                        "      \"node_id\": \"ABC123456789\",\n" +
                        "      \"product_id\": \"ABC123456789\",\n" +
                        "      \"gateway_id\": \"63f5b8324db8e021b6229e14_12336556656564\",\n" +
                        "      \"tags\": [\n" +
                        "        {\n" +
                        "          \"tag_key\": \"testTagName\",\n" +
                        "          \"tag_value\": \"testTagValue\"\n" +
                        "        }\n" +
                        "      ]\n" +
                        "    },\n" +
                        "    \"body\": {\n" +
                        "      \"topic\": \"string\",\n" +
                        "      \"content\": \"string\"\n" +
                        "    }\n" +
                        "  }\n" +
                        "}");
                activity.uploadMesg(message);
            }
        });

        view.findViewById(R.id.tv1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ServiceProperty property = new ServiceProperty();
                property.setServiceId(activity.deviceId);
                Map<String, Object> map = new HashMap<>();
                map.put("aa", "bb");
                property.setProperties(map);
                activity.uploadPro(property);
            }
        });

        //        view.findViewById(R.id.tv2).setOnClickListener(new View.OnClickListener() {
        //            @Override
        //            public void onClick(View v) {
        //                activity.getProperties("63f5b8324db8e021b6229e14_mqttfx","CurrentGood","123");
        //            }
        //        });

        view.findViewById(R.id.tv3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                activity.getShadowData();

            }
        });
    }
}
