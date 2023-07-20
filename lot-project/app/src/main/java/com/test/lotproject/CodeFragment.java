package com.test.lotproject;

import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;

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

public class CodeFragment extends Fragment {
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_code, container, false);
        initView(view);
        return view;
    }

    private void initView(View view) {
        view.findViewById(R.id.paybutton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PayState.setPayment(1);
                System.out.println(PayState.getPayment());
                AlertDialog dialog = new AlertDialog.Builder(getContext())
                        .setIcon(R.drawable.egg)//设置标题的图片
                        .setTitle("提示")//设置对话框的标题
                        .setMessage("感谢支持^^")//设置对话框的内容
                        //设置对话框的按钮
                        .setPositiveButton("确定", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                dialog.dismiss();
                            }
                        }).create();
                dialog.show();
            }
        });

    }
}