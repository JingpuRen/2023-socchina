package com.test.lotproject;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;

import java.util.List;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;



public class FoodAdapter extends RecyclerView.Adapter<FoodAdapter.ViewHolder>{

    private List<FoodBean> mFruitList;
    private Context mContext;

    static class ViewHolder extends RecyclerView.ViewHolder{
        View fruitView;
        ImageView iv_item;
        TextView tv_item_name;
        TextView tv_item_price;
        public ViewHolder(View view){
            super(view);
            fruitView=view;
            iv_item=view.findViewById(R.id.iv_item);
            tv_item_name=view.findViewById(R.id.tv_item_name);
            tv_item_price=view.findViewById(R.id.tv_item_price);
        }
    }
    public FoodAdapter(Context context,List<FoodBean> fruitList) {
        mFruitList=fruitList;
        mContext = context;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view= LayoutInflater.from(parent.getContext()).inflate(R.layout.item_food,parent,false);
        final ViewHolder holder=new ViewHolder(view);
        holder.fruitView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        FoodBean bean=mFruitList.get(position);
        Glide.with(mContext).load(bean.getPic()).into(holder.iv_item);
        holder.tv_item_name.setText(bean.getName());
        holder.tv_item_price.setText(bean.getPrice());
    }

    @Override
    public int getItemCount() {
        return mFruitList.size();
    }

    public void addData(FoodBean bean){
        mFruitList.add(bean);
        notifyDataSetChanged();
    }
}
