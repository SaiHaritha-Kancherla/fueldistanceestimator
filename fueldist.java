package com.example.finpro;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.Map;

public class fueldist extends AppCompatActivity {
    TextView fc,fl,m,d;
    Button btn;
    DatabaseReference reff;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fueldist);

        fc=(TextView) findViewById(R.id.fuelinml);
        fl=(TextView) findViewById(R.id.fuellevel);
        m=(TextView) findViewById(R.id.msg);
        d=(TextView) findViewById(R.id.dist);
        btn=(Button) findViewById(R.id.butres);
        btn.setOnClickListener(new View.OnClickListener()
        {

            @Override
            public void onClick(View view) {
                reff= FirebaseDatabase.getInstance().getReference();
                reff.addValueEventListener(new ValueEventListener() {
                    @Override
                    public void onDataChange(@NonNull DataSnapshot ds) {


                            String fuell=ds.child("fuellevel").getValue().toString();
                            String fuelc=ds.child("fuel").getValue().toString();
                            String ms=ds.child("msg").getValue().toString();
                            String di=ds.child("dist").getValue().toString();

                            fl.setText(fuell);
                            fc.setText(fuelc);
                            m.setText(ms);
                            d.setText(di);
                            Log.v("fuellevel",fuell);
                            Log.v("fuel capacity",fuelc);
                            Log.v("message",ms);
                            Log.v("distance",di);





                    }


                    @Override
                    public void onCancelled(@NonNull DatabaseError error) {
                        Toast.makeText(fueldist.this,"Failed", Toast.LENGTH_LONG).show();

                    }
                });
            }
        });

    }
}