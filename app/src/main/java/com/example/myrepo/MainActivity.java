package com.example.myrepo;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.example.myrepo.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        binding.textView.setText("Hello from my-repo APK");
    }
}
