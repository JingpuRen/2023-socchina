package com.test.lotproject;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Map;
import java.util.Set;

public class GetDev {
    //请在下方完善信息
    //北京4的
    static String HUAWEINAME="yunnnkk";           //华为账号名
    static String IAMINAME="a";             //IAM账户名
    static String IAMPASSWORD="z123456";          //IAM账户密码
    String project_id="7b0d42f747ed496588800887a1d402cc";           //产品ID
    String device_id="6402ebd5b7768d66eb7896af_20222023";            //设备ID


    static String token="";
    public static void main(String args[]) throws Exception{
        getdev();
    }

    public static String gettoken()throws Exception
    {
        String strurl="";
        strurl="https://iam.cn-north-4.myhuaweicloud.com"+"/v3/auth/tokens?nocatalog=false";
        String tokenstr="{"+"\""+"auth"+"\""+": {"+"\""+"identity"+"\""+": {"+"\""+"methods"+"\""+": ["+"\""+"password"+"\""+"],"+"\""+"password"+"\""+": {"+"\""+"user"+"\""+":{"+"\""+"domain\": {\"name\": \""+HUAWEINAME+"\"},\"name\": \""+IAMINAME+"\",\"password\": \""+IAMPASSWORD+"\"}}},\"scope\": {\"project\": {\"name\": \"cn-north-4\"}}}}";
        URL url = new URL(strurl);
        HttpURLConnection urlCon = (HttpURLConnection)url.openConnection();
        urlCon.addRequestProperty("Content-Type", "application/json;charset=utf8");
        urlCon.setDoOutput(true);
        urlCon.setRequestMethod("POST");
        urlCon.setUseCaches(false);
        urlCon.setInstanceFollowRedirects(true);
        urlCon.connect();


        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(urlCon.getOutputStream(),"UTF-8"));
        writer.write(tokenstr);
        writer.flush();
        writer.close();
        Map headers = urlCon.getHeaderFields();
        Set<String> keys = headers.keySet();
        String token = urlCon.getHeaderField("X-Subject-Token");
        System.out.println("X-Subject-Token"+"："+token);
        return  token;
    }


    public static String getdev() throws Exception
    {
        String strurl="https://iotda.cn-north-4.myhuaweicloud.com"+"/v5/iot/%s/devices/%s/shadow";
        String project_id="7b0d42f747ed496588800887a1d402cc";
        String device_id="6402ebd5b7768d66eb7896af_20222023";
        strurl = String.format(strurl, project_id,device_id);
        String  token=gettoken();
        URL url = new URL(strurl);
        HttpURLConnection urlCon = (HttpURLConnection)url.openConnection();
        urlCon.addRequestProperty("Content-Type", "application/json");
        urlCon.addRequestProperty("X-Auth-Token",token);
        urlCon.connect();
        InputStreamReader is = new InputStreamReader(urlCon.getInputStream());
        BufferedReader bufferedReader = new BufferedReader(is);
        StringBuffer strBuffer = new StringBuffer();
        String line = null;
        while ((line = bufferedReader.readLine()) != null) {
            strBuffer.append(line);
        }
        is.close();
        urlCon.disconnect();
        String result = strBuffer.toString();
        System.out.println(result);

        String pro="Name";
        ObjectMapper objectMapper = new ObjectMapper();
        JsonNode jsonNode = objectMapper.readValue(result, JsonNode.class);
        JsonNode tempNode = jsonNode.get("shadow").get(0).get("reported").get("properties").get(pro);
        String attvaluestr = tempNode.asText();
        System.out.println(pro+"=" + attvaluestr);
        return attvaluestr;
    }
}
