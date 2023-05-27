package com.example.mathcalculator;

import android.os.Bundle;

import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;


public class MainFragment extends Fragment implements View.OnClickListener {
    private View view;
    private TextView text_view_output;
    private EditText edit_text_input;
    private FloatingActionButton btn_matrix;
    private Button btn_skobka1, btn_skobka2, btn0, btn1, btn2, btn3, btn4, btn5, btn6;
    private Button btn7, btn8, btn9, btn_mult, btn_div, btn_minus, btn_plus, btn_equal, btn_zap;
    private Button btnX, btn_power;

    public MainFragment() {
        // Required empty public constructor
    }

    public static MainFragment newInstance(String param1, String param2) {
        MainFragment fragment = new MainFragment();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        view = inflater.inflate(R.layout.fragment_main, container, false);
        view.setBackgroundColor(getResources().getColor(R.color.background));
        text_view_output = view.findViewById(R.id.text_view_output);
        text_view_output.setText("Output");

        btn_matrix = view.findViewById(R.id.fab);
        btn_matrix.setOnClickListener(this);

        edit_text_input = (EditText) view.findViewById(R.id.et_input);
        edit_text_input.setShowSoftInputOnFocus(false);
        initButtons();
        return view;
    }

    public void initButtons(){
        btn_skobka1 = view.findViewById(R.id.btn_skobka);
        btn_skobka1.setOnClickListener(this);
        btn_skobka2 = view.findViewById(R.id.btn_skobka2);
        btn_skobka2.setOnClickListener(this);
        btn0 = view.findViewById(R.id.btn_0);
        btn0.setOnClickListener(this);
        btn1 = view.findViewById(R.id.btn_1);
        btn1.setOnClickListener(this);
        btn2 = view.findViewById(R.id.btn_2);
        btn2.setOnClickListener(this);
        btn3 = view.findViewById(R.id.btn_3);
        btn3.setOnClickListener(this);
        btn4 = view.findViewById(R.id.btn_4);
        btn4.setOnClickListener(this);
        btn5 = view.findViewById(R.id.btn_5);
        btn5.setOnClickListener(this);
        btn6 = view.findViewById(R.id.btn_6);
        btn6.setOnClickListener(this);
        btn7 = view.findViewById(R.id.btn_7);
        btn7.setOnClickListener(this);
        btn8 = view.findViewById(R.id.btn_8);
        btn8.setOnClickListener(this);
        btn9 = view.findViewById(R.id.btn_9);
        btn9.setOnClickListener(this);
        btn_mult = view.findViewById(R.id.btn_mult);
        btn_mult.setOnClickListener(this);
        btn_div = view.findViewById(R.id.btn_del);
        btn_div.setOnClickListener(this);
        btn_minus = view.findViewById(R.id.btn_minus);
        btn_minus.setOnClickListener(this);
        btn_plus = view.findViewById(R.id.btn_sum);
        btn_plus.setOnClickListener(this);
        btn_equal = view.findViewById(R.id.btn_equal);
        btn_equal.setOnClickListener(this);
        btn_zap = view.findViewById(R.id.btn_zapyt);
        btn_zap.setOnClickListener(this);
        btnX = view.findViewById(R.id.btn_x);
        btnX.setOnClickListener(this);
        btn_power = view.findViewById(R.id.btn_power);
        btn_power.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        if (v == btn_matrix) {
            ((NavigationHost) getActivity()).navigateTo(new MatrixFragment(), true);
        } else if (v == btn0) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "0");
        } else if (v == btn1) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "1");
        } else if (v == btn2) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "2");
        } else if (v == btn3) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "3");
        } else if (v == btn4) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "4");
        } else if (v == btn5) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "5");
        } else if (v == btn6) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "6");
        } else if (v == btn7) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "7");
        } else if (v == btn8) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "8");
        } else if (v == btn9) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "9");
        } else if (v == btn_div) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "/");
        } else if (v == btn_plus) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "+");
        } else if (v == btn_minus) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "-");
        } else if (v == btn_mult) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "⋅");
        } else if (v == btn_equal) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "=");
        } else if (v == btn_zap) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + ",");
        } else if (v == btnX) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "X");
        } else if (v == btn_power) {
            String text = edit_text_input.getText().toString();
            edit_text_input.setText(text + "X^2");
        }
    }
}