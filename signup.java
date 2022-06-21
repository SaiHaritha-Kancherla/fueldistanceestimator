package com.example.finpro;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.FirebaseDatabase;

public class signup extends AppCompatActivity implements View.OnClickListener {
    private FirebaseAuth mAuth;

    private TextView banner,registeruser;
    private EditText etfullname,etemail,etpswd,etfuelcapacity,etphnno,etbikemodel,etmileage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_signup);

        mAuth=FirebaseAuth.getInstance();

//        banner=(TextView) findViewById(R.id.banner);
//        banner.setOnClickListener(this);

        registeruser=(Button) findViewById(R.id.signup);
        registeruser.setOnClickListener(this);

        etfullname=(EditText) findViewById(R.id.fullname);
        etemail=(EditText) findViewById(R.id.email);
        etpswd=(EditText) findViewById(R.id.password);
        etfuelcapacity=(EditText) findViewById(R.id.fuelcapacity);

        etphnno=(EditText) findViewById(R.id.phnno);
        etbikemodel=(EditText) findViewById(R.id.bikemodel);
        etmileage=(EditText) findViewById(R.id.vehiclemileage);















    }

    @Override
    public void onClick(View v) {
        switch(v.getId())
        {
            case R.id.signup:
                signup();
                break;
        }

    }


    private void signup()
    {
        String email=etemail.getText().toString().trim();
        String fullname=etfullname.getText().toString().trim();
        String password=etpswd.getText().toString().trim();
        String fuelcapacity=etfuelcapacity.getText().toString().trim();

        String phnno=etphnno.getText().toString().trim();
        String mileage=etmileage.getText().toString().trim();
        String bikemodel=etbikemodel.getText().toString().trim();

        if(fullname.isEmpty())
        {
            etfullname.setError("Full Name is required");
            etfullname.requestFocus();
            return;
        }
        if(email.isEmpty())
        {
            etemail.setError("email is required");
            etemail.requestFocus();
            return;
        }
        if(password.isEmpty())
        {
            etpswd.setError("Password is required");
            etpswd.requestFocus();
            return;
        }
        if(fuelcapacity.isEmpty())
        {
            etfuelcapacity.setError("Tank depth is required");
            etfuelcapacity.requestFocus();
            return;
        }

        if(phnno.isEmpty())
        {
            etphnno.setError("Phone number is required");
            etphnno.requestFocus();
            return;
        }
        if(mileage.isEmpty())
        {
            etmileage.setError("Mileage is required");
            etmileage.requestFocus();
            return;
        }
        if(bikemodel.isEmpty())
        {
            etbikemodel.setError("Bikemodel  is required");
            etbikemodel.requestFocus();
            return;
        }
        mAuth.createUserWithEmailAndPassword(email,password)
                .addOnCompleteListener(new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        if(task.isSuccessful())
                        {
                            user u=new user(fullname,email,password,mileage,fuelcapacity,bikemodel,phnno);
                            FirebaseDatabase.getInstance().getReference("users")
                                    .child(FirebaseAuth.getInstance().getCurrentUser().getUid())
                                    .setValue(u).addOnCompleteListener(new OnCompleteListener<Void>() {
                                @Override
                                public void onComplete(@NonNull Task<Void> task) {
                                    if(task.isSuccessful())
                                    {

                                        Intent idist = new Intent(signup.this,fueldist.class);
                                        startActivity(idist);

                                    }
                                    else
                                    {
                                        Toast.makeText(signup.this,"Registration Unsuccessfull Try Again",Toast.LENGTH_LONG).show();
                                    }
                                }
                            });


                        }
                        else
                        {
                            Toast.makeText(signup.this,"Registration Unsuccessfull Try Again",Toast.LENGTH_LONG).show();
                        }
                    }
                });

    }
}