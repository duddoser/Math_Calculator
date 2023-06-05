package com.example.mathcalculator;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;

import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;

import android.text.Editable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import org.mariuszgromada.math.mxparser.*;

import com.google.android.material.dialog.MaterialAlertDialogBuilder;
import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.util.ArrayList;


public class MainFragment extends Fragment implements View.OnClickListener {
    private View view;
    private TextView text_view_output;
    private EditText edit_text_input;
    private FloatingActionButton btn_matrix, btn_proceed;
    private Button btn1, btn2;
    private ArrayList<Button> buttons, buttons2;
    private String[] alphabet = {"(", "7", "8", "9", "/", ")", "4", "5",
                                "6", "*", "x", "1", "2", "3", "-", "x^2", "0", ".", "^", "+"};
    private String[] alphabet2 = {"exp", "ln", "cos", "sin", "tg", "ctg", "sec", "cosec", "asin",
            "acos", "atg", "actg", "log2", "lg", "sinh", "cosh", "tgh", "ctgh", "abs", "sqrt"};
    private String point;
    private LinearLayout keyboard1, keyboard2;

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

        btn1 = view.findViewById(R.id.btn_keyboard1);
        btn1.setOnClickListener(this);

        btn2 = view.findViewById(R.id.btn_keyboard2);
        btn2.setOnClickListener(this);

        keyboard1 = view.findViewById(R.id.linear_layout_first_keyboard);
        keyboard2 = view.findViewById(R.id.linear_layout_second_keyboard);
        keyboard2.setVisibility(View.INVISIBLE);
        keyboard2.setVisibility(View.GONE);

        btn_matrix = view.findViewById(R.id.fab);
        btn_matrix.setOnClickListener(this);

        btn_proceed = view.findViewById(R.id.fab2);
        btn_proceed.setOnClickListener(this);

        edit_text_input = view.findViewById(R.id.et_input);
        edit_text_input.setShowSoftInputOnFocus(false);

        initButtons();
        return view;
    }

    public void initButtons(){
        buttons = new ArrayList<>();
        for (int i = 0; i < 20; i++) {
            String button_id = "btn_main_" + i;
            buttons.add(view.findViewById(getResources().getIdentifier(button_id,
                    "id", getActivity().getPackageName())));
            buttons.get(i).setOnClickListener(this);
        }

        buttons2 = new ArrayList<>();
        for (int i = 0; i < 20; i++) {
            String button_id = "btn_sec_" + i;
            buttons2.add(view.findViewById(getResources().getIdentifier(button_id,
                    "id", getActivity().getPackageName())));
            buttons2.get(i).setOnClickListener(this);
        }
    }

    @Override
    public void onClick(View v) {
        if (v == btn_matrix) {
            ((NavigationHost) getActivity()).navigateTo(new MatrixFragment(), true);
        } else if (v == btn_proceed) {
            createAlertDialog();
        } else if (v == btn1) {
            keyboard1.setVisibility(View.VISIBLE);
            keyboard2.setVisibility(View.INVISIBLE);
            keyboard2.setVisibility(View.GONE);
        } else if (v == btn2) {
            keyboard2.setVisibility(View.VISIBLE);
            keyboard1.setVisibility(View.INVISIBLE);
            keyboard1.setVisibility(View.GONE);
        } else {
            String text = edit_text_input.getText().toString();

            if (keyboard1.getVisibility() == View.VISIBLE) {
                for (int i = 0; i < 20; i++) {
                    if (buttons.get(i).isPressed()) {
                        edit_text_input.setText(text + alphabet[i]);
                    }
                }
            } else {
                for (int i = 0; i < 20; i++) {
                    if (buttons2.get(i).isPressed()) {
                        edit_text_input.setText(text + alphabet2[i]);
                    }
                }
            }
        }
    }

    public void setPoint(String text) {
        point = text;
    }

    public void createAlertDialog() {
        AlertDialog.Builder alert = new AlertDialog.Builder(this.getContext());
        EditText editText = new EditText(this.getContext());
        alert.setTitle("Enter x value:");
        alert.setView(editText);

        alert.setPositiveButton("Enter", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                String textValue = editText.getText().toString();
                setPoint(textValue);
                formatInput(edit_text_input.getText().toString());
            }
        });
        alert.show();
    }

    public void formatInput(String input) {
        Log.e("AAAAAAAAAA", input);
        Function inputFunction = new Function("F(x) = " + input);
        Argument x = new Argument("x = " + point);
        Expression expression = new Expression("F(x)", inputFunction, x);
        String result = String.valueOf(expression.calculate());
        if (result.equals("NaN")) {
            text_view_output.setText("TypeError: check your input");
        } else {
            String text = expression.getExpressionString() + "=" + result;
            text_view_output.setText(text);
        }
    }
}