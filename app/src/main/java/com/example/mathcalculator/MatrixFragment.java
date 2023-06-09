package com.example.mathcalculator;

import android.os.Bundle;

import androidx.core.content.ContextCompat;
import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;

import android.text.InputType;
import android.util.Log;
import android.util.Pair;
import android.view.ContextThemeWrapper;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.google.android.material.dialog.MaterialAlertDialogBuilder;
import com.google.android.material.textfield.TextInputEditText;
import com.google.android.material.textfield.TextInputLayout;

import java.util.ArrayList;
import java.util.HashMap;

public class MatrixFragment extends Fragment implements CustomDialogInterface, View.OnClickListener {
    private View view;
    private int height, width;
    private Button btnDeterminant, btnSole;
    private ArrayList<EditText> etArray = new ArrayList<>();

    static {
        System.loadLibrary("mathcalculator");
    }

    public MatrixFragment() {
        // Required empty public constructor
    }

    public static MatrixFragment newInstance(String param1, String param2) {
        MatrixFragment fragment = new MatrixFragment();
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
        view = inflater.inflate(R.layout.fragment_matrix, container, false);

        DialogFragment fragment = new DialogFragmentMatrix(this);
        fragment.show(getFragmentManager(), "dialog");

        btnDeterminant = view.findViewById(R.id.determinant);
        btnSole = view.findViewById(R.id.sole);
        btnDeterminant.setOnClickListener(this);
        btnSole.setOnClickListener(this);
        return view;
    }

    public void generateMatrix() {
        TableLayout table = view.findViewById(R.id.table_layout);
        for (int i = 0; i < height; i++) {
            TableRow row = new TableRow(this.getContext());
            row.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT));
            for (int j = 0; j < width; j++) {
//                TextInputEditText cell = generateTextField();
                EditText cell = new EditText(this.getContext());
                etArray.add(i * width + j, cell);
                // не воспринимает числа с плавающей точкой
                cell.setInputType(InputType.TYPE_CLASS_NUMBER);
                cell.setBackground(null);
                cell.setText("0");
                row.addView(cell);
            }
            table.addView(row, new TableLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT));
        }

//        ImageView bracket_left = view.findViewById(R.id.bracket_left);
//        ImageView bracket_right = view.findViewById(R.id.bracket_right);
//
//        LinearLayout.LayoutParams parms = new LinearLayout.LayoutParams(10, 20 + etArray.get(0).getHeight() * height);
//        bracket_left.setLayoutParams(parms);
//        bracket_right.setLayoutParams(parms);

    }

//    protected TextInputEditText generateTextField() {
//        TextInputLayout textInputLayout = new TextInputLayout(new ContextThemeWrapper(getContext(),
//                R.style.Widget_MaterialComponents_TextInputLayout_OutlinedBox));
//        textInputLayout.setBoxBackgroundColor(ContextCompat.getColor(getContext(),
//                android.R.color.white));
//        textInputLayout.setBoxBackgroundMode(TextInputLayout.BOX_BACKGROUND_OUTLINE);
//
//        TextInputEditText editText = new TextInputEditText(textInputLayout.getContext());
//        return editText;
//    }

    @Override
    public void okButtonClicked(Pair<Integer, Integer> value) {
        height = (int) value.first;
        width = (int) value.second;
        Log.e("AAAAA", Integer.toString(height));
        generateMatrix();
    }

    @Override
    public void onClick(View v) {
        if (v == btnDeterminant) {
            TextView textViewDet = view.findViewById(R.id.tv_det_res);
            double [] mat = new double[height * width];
            int k = 0;
            for (int i = 0; i < height * width; i++) {
                mat[i] = Double.parseDouble(etArray.get(k).getText().toString());
            }

//            double result = NdkManager.determinantOfMatrix(height, mat);
            double result = 10;
            textViewDet.setText("Determinant: " + result);
            
        } else if (v == btnSole) {
            double [] mat = new double[height * width];
            int k = 0;
            for (int i = 0; i < height * width; i++) {
                mat[i] = Double.parseDouble(etArray.get(k).getText().toString());
            }

            ArrayList<TextView> eq_results = new ArrayList<>();
            for (int i = 1; i < height + 1; i++) {
                String text_view_id = "x" + i;
                eq_results.add(view.findViewById(getResources().getIdentifier(text_view_id,
                        "id", getActivity().getPackageName())));
            }

//            for (int i = 0; i < height; i++) {
//                eq_results.get(i).setText(Double.toString(x[i]));
//            }

        }
    }

}