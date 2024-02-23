package com.example.car_ble;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.provider.Settings;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import java.io.IOException;
import java.util.Set;
import java.util.UUID;

import android.Manifest;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static final int LOCATION_PERMISSION_REQUEST_CODE = 123;

    private static LinearLayout ll_cart;
    private BluetoothAdapter bluetoothAdapter;
    UUID MY_UUID = UUID.fromString("00000000-0000-1000-8000-00805F9B34FB");

    @SuppressLint("Range")
    @RequiresApi(api = Build.VERSION_CODES.UPSIDE_DOWN_CAKE)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ll_cart = findViewById(R.id.ll_cart);
        if (enableBL()) return; // 添加 return，以防止继续执行后续代码
        addPair();
        isLocation();
        findBL();
    }

    //开启位置权限
    private void startLocation() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this, android.R.style.Theme_DeviceDefault_Light_Dialog_Alert);
        builder.setTitle("提示")
                .setMessage("请前往打开手机的位置权限!")
                .setCancelable(false)
                .setPositiveButton("确定", (dialog, which) -> {
                    Intent intent = new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
                    startActivityForResult(intent, 10);
                }).show();
    }

    private void findBL() {
        // Register for broadcasts when a device is discovered.
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        registerReceiver(receiver, filter);

        // Start discovery process
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_SCAN) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return;
        }
        bluetoothAdapter.startDiscovery();
    }

    private void isLocation() {
        // 检查是否已经获取了定位权限
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            // 请求定位权限
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION}, LOCATION_PERMISSION_REQUEST_CODE);
            startLocation();
        } else {
            // 已经获取了定位权限，可以开始相应的操作
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        //退出这个界面，或是返回桌面时，停止扫描
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_SCAN) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return;
        }
        bluetoothAdapter.cancelDiscovery();

    }
    private void addPair() {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return;
        }
        Set<BluetoothDevice> pairedDevices = bluetoothAdapter.getBondedDevices();

        if (pairedDevices.size() > 0) {
            // There are paired devices. Get the name and address of each paired device.
            for (BluetoothDevice device : pairedDevices) {
                enableBL(device, true);
            }
        }
    }

    private boolean enableBL() {
        BluetoothManager bluetoothManager = getSystemService(BluetoothManager.class);
        bluetoothAdapter = bluetoothManager.getAdapter();
        if (bluetoothAdapter == null) {
            // Device doesn't support Bluetooth
            Toast.makeText(this, "本设备不支持蓝牙", Toast.LENGTH_SHORT).show();
            finish();
            return true;
        }

        // 如果蓝牙未启用，则尝试启用蓝牙
        if (!bluetoothAdapter.isEnabled()) {
            enableBluetooth(); // 启用蓝牙
        }
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
            return true;
        }
        return false;
    }

    private void enableBL(BluetoothDevice device, boolean isPair) {
        View view = LayoutInflater.from(this).inflate(R.layout.item_recycler_main, null);
        TextView item_main_beacon = view.findViewById(R.id.item_main_beacon);
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {

            return;
        }
        item_main_beacon.setText(device.getName());
        TextView item_main_mac = view.findViewById(R.id.item_main_mac);
        item_main_mac.setText(device.getAddress());
        TextView item_main_rssi = view.findViewById(R.id.item_main_rssi);
        if (isPair) {
            item_main_rssi.setText("已配对");
        } else {
            item_main_rssi.setText("未配对");
        }
        // 将 BluetoothDevice 对象附加到 View 上
        view.setTag(device);

        view.setOnClickListener(this);

        ll_cart.addView(view);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == LOCATION_PERMISSION_REQUEST_CODE) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                // 用户已授予定位权限，可以开始相应的操作
            } else {
                // 用户拒绝了定位权限请求，您可以给出相应的提示或采取其他适当的措施
                Toast.makeText(this, "没有定位权限", Toast.LENGTH_SHORT).show();
            }
        }
    }


    // Create a BroadcastReceiver for ACTION_FOUND.
    private final BroadcastReceiver receiver = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();

            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                // Discovery has found a device. Get the BluetoothDevice
                // object and its info from the Intent.
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);

                if (ActivityCompat.checkSelfPermission(MainActivity.this, android.Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
                    // TODO: Consider calling
                    //    ActivityCompat#requestPermissions
                    // here to request the missing permissions, and then overriding
                    //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                    //                                          int[] grantResults)
                    // to handle the case where the user grants the permission. See the documentation
                    // for ActivityCompat#requestPermissions for more details.
                    return;
                }
                enableBL(device, false);

            }
        }
    };


    private final ActivityResultLauncher<Intent> enableBtLauncher = registerForActivityResult(new ActivityResultContracts.StartActivityForResult(),
            result -> {
                if (result.getResultCode() == Activity.RESULT_OK) {
                } else {
                    // 用户未启用蓝牙，可以给出相应的提示
                    Toast.makeText(this, "未启用蓝牙", Toast.LENGTH_SHORT).show();
                    enableBluetooth();
                }
            });

    // 在需要启用蓝牙的地方调用该方法
    private void enableBluetooth() {
        Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
        enableBtLauncher.launch(enableBtIntent);
    }


    @Override
    public void onClick(View v) {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.BLUETOOTH_SCAN) != PackageManager.PERMISSION_GRANTED) {
            return;
        }
        bluetoothAdapter.cancelDiscovery();

        BluetoothDevice device = (BluetoothDevice) v.getTag();

        Intent intent = new Intent(this, controlActivity.class);
        intent.putExtra("bluetooth_device", device); // 将BluetoothDevice对象放入Intent的Extras中
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(intent);

    }
    @Override
    protected void onDestroy() {
        super.onDestroy();

        // Don't forget to unregister the ACTION_FOUND receiver.
        unregisterReceiver(receiver);
    }
}




