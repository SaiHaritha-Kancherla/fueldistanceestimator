package com.example.finpro;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void login(View view) {
        Intent il = new Intent(this, login.class);
        startActivity(il);

    }




    public void signup(View view) {
        Intent isi = new Intent(this, signup.class);
        startActivity(isi);

    }


}