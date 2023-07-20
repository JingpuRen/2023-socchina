package com.test.lotproject;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

import java.util.ArrayList;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;


public class FoodFragment extends Fragment {

    private RecyclerView rv;
    private TextView tv;
    private FoodAdapter mAdapter;
    private double count;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_food, container, false);
        if (!EventBus.getDefault().isRegistered(this)) {
            EventBus.getDefault().register(this);
        }
        initView(view);
        return view;
    }

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        if (EventBus.getDefault().isRegistered(this)) {
            EventBus.getDefault().unregister(this);
        }
    }

    private void initView(View view) {
        rv = view.findViewById(R.id.rv);
        tv = view.findViewById(R.id.tv);
        rv.setLayoutManager(new LinearLayoutManager(getContext()));
        mAdapter = new FoodAdapter(getContext(),new ArrayList<FoodBean>());
        rv.setAdapter(mAdapter);

    }


    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onEvent(FoodBean bean) {
        if (bean.getType() == 1) {
            mAdapter.addData(bean);
            String price = bean.getPrice();
            try {
                double v = Double.parseDouble(price);
                count += v;
                tv.setText("总计："+count);
            }catch (Exception e){}
        }
    }
}
