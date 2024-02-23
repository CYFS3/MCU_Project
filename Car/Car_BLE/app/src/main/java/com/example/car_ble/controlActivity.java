package com.example.car_ble;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.IntentFilter;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.io.Writer;
import java.util.UUID;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class controlActivity extends AppCompatActivity implements View.OnTouchListener {

    private OutputStream outputStream;
    private Handler handler;
    private BluetoothSocket socket;
    private TextView tv_link;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);

        BluetoothDevice device = getIntent().getParcelableExtra("bluetooth_device");
        if (device != null) {

            new Thread(new Runnable() {
                @Override
                public void run() {
                    // 在这个线程中执行耗时的连接操作
                    connectToDevice(device);
                }
            }).start();

        }

        findViewById(R.id.bt_back).setOnTouchListener(this);
        findViewById(R.id.bt_font).setOnTouchListener(this);
        findViewById(R.id.bt_legh).setOnTouchListener(this);
        findViewById(R.id.bt_right).setOnTouchListener(this);
        // 创建定时任务调度器，每隔1秒执行一次 checkConnectionStatus 方法
        handler = new Handler(Looper.getMainLooper());
        ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);
        scheduler.scheduleAtFixedRate(this::checkConnectionStatus, 0, 1, TimeUnit.SECONDS);
        tv_link = findViewById(R.id.tv_link);
    }
    private void checkConnectionStatus() {
        // 在非主线程中执行 UI 操作
        new Thread(() -> {
            // 进行一些耗时操作

            // 使用 Handler 切换到主线程执行 UI 操作
            new Handler(Looper.getMainLooper()).post(() -> {
                // 在这里执行 UI 操作
                handler.post(() -> {

                    if (socket != null && socket.isConnected()) {
                        tv_link.setText("已连接");
                        tv_link.setTextColor(0xFF0000FF);

                    } else {
                        tv_link.setText("未连接");
                        tv_link.setTextColor(0xFFFF0000);
                    }

                });
            });
        }).start();
    }
    private void connectToDevice(BluetoothDevice device) {
        // 执行蓝牙连接操作，并处理连接结果
        socket = null;
        try {
            // 使用UUID创建BluetoothSocket
            UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"); // 这是一个通用的UUID，用于串口通信
            if (ActivityCompat.checkSelfPermission(this, android.Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                // TODO: Consider calling
                //    ActivityCompat#requestPermissions
                // here to request the missing permissions, and then overriding
                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                //                                          int[] grantResults)
                // to handle the case where the user grants the permission. See the documentation
                // for ActivityCompat#requestPermissions for more details.
                return;
            }
            socket = device.createRfcommSocketToServiceRecord(MY_UUID);
            // 连接到BluetoothSocket
            socket.connect();

            // 如果连接成功，则可以在这里进行通信
            // 例如，发送和接收数据
            // 获取BluetoothSocket的OutputStream
            outputStream = socket.getOutputStream();



        } catch (IOException e) {
            // 连接过程中出现异常处理
            e.printStackTrace();
            try {
                // 关闭连接
                if (socket != null) {
                    socket.close();
                }
            } catch (IOException closeException) {
                closeException.printStackTrace();
            }
        }
    }

    private final  byte dataByteA = 0x41; // 例如，发送ASCII字符'A'
    private final  byte dataByteW = 0x57; // 例如，发送ASCII字符'A'
    private final  byte dataByteD = 0x44; // 例如，发送ASCII字符'A'
    private final  byte dataByteS = 0x53; // 例如，发送ASCII字符'A'
    private final  byte dataByte = 0x33; // 例如，发送ASCII字符'A'


    @Override
    protected void onDestroy() {
        super.onDestroy();

        try {
            socket.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void sendByte(byte Byte) {
        try {
            outputStream.write(Byte);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @SuppressLint("ClickableViewAccessibility")
    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if(outputStream == null || (socket != null && !socket.isConnected())){
            Toast.makeText(this,"蓝牙未连接",Toast.LENGTH_SHORT).show();
            return true;
        }
        if (event.getAction() == MotionEvent.ACTION_UP) {
            // 在按钮松开时执行的操作
            sendByte(dataByte);
            return true; // 返回true表示已处理该触摸事件
        } else if (event.getAction() == MotionEvent.ACTION_DOWN) {
            int id  = v.getId();

            if(id == R.id.bt_right){
                sendByte(dataByteD);
            } else if (id == R.id.bt_legh) {
                sendByte(dataByteA);
            } else if (id == R.id.bt_font) {
                sendByte(dataByteW);
            } else if (id == R.id.bt_back) {
                sendByte(dataByteS);
            }
            return true;
        }
        return false;
    }
}