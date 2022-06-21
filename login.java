package com.example.finpro;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Patterns;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;

public class login extends AppCompatActivity implements View.OnClickListener {
    String email,pswd;
    private EditText e,p;
    private Button blogin;
    private FirebaseAuth mauth;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        e=(EditText)findViewById(R.id.email);
        p=(EditText) findViewById(R.id.pswd);
        blogin=(Button) findViewById(R.id.login);
        blogin.setOnClickListener(this);
        mauth=FirebaseAuth.getInstance();

    }


    @Override
    public void onClick(View view) {
        String em=e.getText().toString().trim();
        String password=p.getText().toString().trim();
        if(em.isEmpty())
        {
            e.setError("Email is required!");
            e.requestFocus();
            return;
        }
        if(!(Patterns.EMAIL_ADDRESS.matcher(em).matches()))
        {
            e.setError("Invalid Email id");
            e.requestFocus();
            return;

        }
        if(password.isEmpty())
        {
            p.setError("Password is required!");
            p.requestFocus();
            return;
        }
        if(password.length()<6)
        {
            p.setError("Password length should be greater than 6");
            p.requestFocus();
            return;
        }
        mauth.signInWithEmailAndPassword(em,password).addOnCompleteListener(new OnCompleteListener<AuthResult>() {
            @Override
            public void onComplete(@NonNull Task<AuthResult> task) {
                if(task.isSuccessful())
                {
                    startActivity(new Intent(login.this,fueldist.class));

                }
                else
                {
                    Toast.makeText(login.this,"Failed to login!Please Enter valid credentials",Toast.LENGTH_LONG).show();

                }
            }
        });

    }
}