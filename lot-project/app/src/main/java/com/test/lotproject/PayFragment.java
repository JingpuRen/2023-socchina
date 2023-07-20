package com.test.lotproject;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;

import androidx.annotation.MainThread;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.os.Looper;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import java.util.Timer;
import java.util.TimerTask;


public class PayFragment extends Fragment {
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_pay, container, false);
        initView(view);
        return view;
    }

    private void initView(View view) {
        final MainActivity activity = (MainActivity) getActivity();
        view.findViewById(R.id.pay1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlertDialog dialog = new AlertDialog.Builder(getContext())
                        .setIcon(R.drawable.egg)//设置标题的图片
                        .setTitle("提示")//设置对话框的标题
                        .setMessage("点击右下角查看二维码")//设置对话框的内容
                        //设置对话框的按钮

                        .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                Toast.makeText(getContext(), "感谢支持", Toast.LENGTH_SHORT).show();
                                dialog.dismiss();
                            }
                        }).create();
                dialog.show();
            }
        });
        view.findViewById(R.id.pay2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PayState.setPayment(1);
                final Context context=getContext();
                /*final ProgressDialog dialog = new ProgressDialog(getContext());
                dialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
                dialog.setMessage("正在识别中");
                dialog.setMax(100);
                final Timer timer = new Timer();
                timer.schedule(new TimerTask() {
                    int progress = 0;
                    @Override
                    public void run() {
                        dialog.setProgress(progress += 10);
                        if (progress >= 100) {
                            timer.cancel();
                            dialog.dismiss();
                        }
                    }
                }, 0, 1000);
                dialog.show();*/
                AlertDialog dialoga = new AlertDialog.Builder(getContext())
                        .setIcon(R.drawable.egg)//设置标题的图片
                        .setTitle("提示")//设置对话框的标题
                        .setMessage("请扫脸后点击确认")//设置对话框的内容
                        //设置对话框的按钮
                        .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                final String[] str = {""};
                                //获取影子属性
                                new Thread(new Runnable() {
                                    @Override
                                    public void run() {
                                        try {
                                            str[0] = GetDev.getdev();
                                            System.out.println(str[0]);
                                            //子线程中调用toast需要looper
                                            Looper.prepare();
                                            AlertDialog dialog = new AlertDialog.Builder(getContext())
                                                    .setIcon(R.drawable.egg)//设置标题的图片
                                                    .setTitle("提示")//设置对话框的标题
                                                    .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                                                        @Override
                                                        public void onClick(DialogInterface dialog, int which) {

                                                            dialog.dismiss();
                                                        }
                                                    }).create();
                                            int a=Integer.valueOf(str[0]);
                                            if(a==1){
                                                dialog.setMessage("陈博昉支付成功");
                                                Toast.makeText(getContext(), "人脸支付成功", Toast.LENGTH_SHORT).show();
                                            }
                                            if(a==2){
                                                dialog.setMessage("陈益鸿支付成功");
                                                Toast.makeText(getContext(), "人脸支付成功", Toast.LENGTH_SHORT).show();
                                            }
                                            if(a==3){
                                                dialog.setMessage("张颖格支付成功");
                                                Toast.makeText(getContext(), "人脸支付成功", Toast.LENGTH_SHORT).show();
                                            }

                                            dialog.show();
                                            Looper.loop();
                                        } catch (Exception e) {
                                            e.printStackTrace();
                                        }
                                    }
                                }).start();

                                dialog.dismiss();

                            }
                        }).create();
                dialoga.show();


            }
        });
        view.findViewById(R.id.pay3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PayState.setPayment(1);
                final Context context=getContext();
                final ProgressDialog dialog = new ProgressDialog(getContext());
                dialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
                dialog.setMessage("正在识别中");
                dialog.setMax(100);
                final Timer timer = new Timer();
                timer.schedule(new TimerTask() {
                    int progress = 0;
                    @Override
                    public void run() {
                        dialog.setProgress(progress += 5);
                        if (progress >= 100) {
                            timer.cancel();
                            dialog.dismiss();
                            Looper.prepare();
                            AlertDialog dialogA = new AlertDialog.Builder(getContext())
                                    .setIcon(R.drawable.egg)//设置标题的图片
                                    .setTitle("提示")//设置对话框的标题
                                    .setMessage("碰一碰支付成功")//设置对话框的内容
                                    //设置对话框的按钮

                                    .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                                        @Override
                                        public void onClick(DialogInterface dialog, int which) {
                                            Toast.makeText(getContext(), "感谢支持", Toast.LENGTH_SHORT).show();
                                            dialog.dismiss();
                                        }
                                    }).create();
                            dialogA.show();
                            Looper.loop();
                            /*//子线程中调用toast需要looper
                            Looper.prepare();
                            Toast.makeText(getActivity(),"碰一碰支付成功",Toast.LENGTH_LONG).show();
                            Looper.loop();*/
                        }
                    }
                }, 0, 1000);
                dialog.show();
            }
        });
        view.findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AlertDialog dialog = new AlertDialog.Builder(getContext())
                        .setIcon(R.drawable.egg)//设置标题的图片
                        .setTitle("提示")//设置对话框的标题

                        //.setMessage("点击下方二维码")//设置对话框的内容
                        //设置对话框的按钮

                        .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                Toast.makeText(getContext(), "感谢支持^^", Toast.LENGTH_SHORT).show();
                                dialog.dismiss();
                            }
                        }).create();
                if(PayState.getPayment()==1){
                    dialog.setMessage("您已经支付过，请勿重复支付");
                }
                else{
                    dialog.setMessage("您还未支付，请选择支付方式");
                }
                dialog.show();
            }
        });
    }
}