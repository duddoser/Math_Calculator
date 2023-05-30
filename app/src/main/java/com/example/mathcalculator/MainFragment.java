package com.example.mathcalculator;

import android.os.Bundle;

import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.ArrayList;


public class MainFragment extends Fragment implements View.OnClickListener {
    private View view;
    private TextView text_view_output;
    private EditText edit_text_input;
    private FloatingActionButton btn_matrix;
    private Button btn_skobka1, btn_skobka2, btn0, btn1, btn2, btn3, btn4, btn5, btn6;
    private Button btn7, btn8, btn9, btn_mult, btn_div, btn_minus, btn_plus, btn_equal, btn_zap;
    private ArrayList<Button> buttons;
    private String[] alphabet = {"(", "7", "8", "9", "/", ")", "4", "5",
                                "6", "⋅", "x", "1", "2", "3", "-", "x^2", "0", ",", "=", "+"};
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

        edit_text_input = view.findViewById(R.id.et_input);
        edit_text_input.setShowSoftInputOnFocus(false);
        initButtons();
        return view;
    }

    public void initButtons(){
        buttons = new ArrayList<>();
        for (int i = 0; i < 20; i++) {
            String button_id = "btn_main_" + i;
            Log.e("AAAAAAA", button_id);
            buttons.add(view.findViewById(getResources().getIdentifier(button_id,
                    "id", getActivity().getPackageName())));
            buttons.get(i).setOnClickListener(this);
        }
    }

    @Override
    public void onClick(View v) {
        if (v == btn_matrix) {
            ((NavigationHost) getActivity()).navigateTo(new MatrixFragment(), true);
        } else {
            String text = edit_text_input.getText().toString();
            for (int i = 0; i < 20; i++) {
                if (buttons.get(i).isPressed()) {
                    edit_text_input.setText(text + alphabet[i]);
                }
            }
        }
    }
}