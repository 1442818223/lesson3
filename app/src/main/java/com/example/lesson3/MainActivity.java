package com.example.lesson3;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.topjohnwu.superuser.ipc.RootService;

public class MainActivity extends AppCompatActivity {

    public static ITestService iTestService;
    class AIDLConnection implements ServiceConnection {

        private final boolean isDaemon;

        AIDLConnection(boolean b) {
            isDaemon = b;
        }

        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            iTestService= ITestService.Stub.asInterface(service);
            Log.d("Shocker","Connected");
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            Log.d("Shocker","Disconnected");

        }
    }

    public int pid;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        Button t=findViewById(R.id.sample_text);

        RootService.bind(new Intent(this, AIDLService.class), new AIDLConnection(false));
        t.setOnClickListener(view -> {
            try {
                Log.d("Shocker","getPid:"+iTestService.getPid());
                Log.d("Shocker","getUid:"+iTestService.getUid());
                Log.d("Shocker","从native层拿到的应用PID:"+iTestService.HHH("bin.mt.plus"));
                pid = iTestService.HHH("bin.mt.plus");
                Toast.makeText(getApplication(), "结果："+pid, Toast.LENGTH_SHORT).show();

            } catch (RemoteException e) {
                e.printStackTrace();
            }


        });
    }


}