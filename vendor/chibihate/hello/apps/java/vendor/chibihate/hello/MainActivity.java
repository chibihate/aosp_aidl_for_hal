package vendor.chibihate.hello;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.util.Log;
import android.os.ServiceManager;
import android.os.IBinder;
import android.hardware.hello.IHello;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "HELLO_TAG";
    private static final String IHELLO_AIDL_INTERFACE = "android.hardware.hello.IHello/default";
    private static IHello helloAJ; // AIDL Java

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btn = (Button) findViewById(R.id.button);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText editText = (EditText) findViewById(R.id.editText);
                String txt = editText.getText().toString();
                Log.d(TAG, "App: request= " + txt);

                if (helloAJ != null) {
                    try {
                        helloAJ.putChars(txt);
                    } catch (android.os.RemoteException e) {
                        Log.e(TAG, "IHello-AIDL error", e);
                    }
                }

                String ret = "";

                if (helloAJ != null) {
                    try {
                        ret = helloAJ.getChars();
                    } catch (android.os.RemoteException e) {
                        Log.e(TAG, "IHello-AIDL error", e);
                    }
                }

                Log.d(TAG, "App: get= " + ret);

                TextView tv = (TextView) findViewById(R.id.textView);
                tv.setText(ret);
            }
        });

        IBinder binder = ServiceManager.getService(IHELLO_AIDL_INTERFACE);
        if (binder == null) {
            Log.e(TAG, "Getting " + IHELLO_AIDL_INTERFACE + " service daemon binder failed!");
        } else {
            helloAJ = IHello.Stub.asInterface(binder);
            if (helloAJ == null) {
                Log.e(TAG, "Getting IHello AIDL daemon interface failed!");
            } else {
                Log.d(TAG, "IHello AIDL daemon interface is binded!");
            }
        }
    }
}