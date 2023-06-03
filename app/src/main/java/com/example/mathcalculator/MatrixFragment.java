package com.example.mathcalculator;

import android.os.Bundle;

import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;

import android.text.InputType;
import android.util.Log;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.google.android.material.dialog.MaterialAlertDialogBuilder;

import java.util.ArrayList;
import java.util.HashMap;

public class MatrixFragment extends Fragment implements CustomDialogInterface, View.OnClickListener {
    private View view;
    private int height, width;
    private Button btnDeterminant, btnSole;
    private ArrayList<EditText> etArray = new ArrayList<>();

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
                EditText cell = new EditText(this.getContext());
                etArray.add(i * width + j, cell);
                cell.setInputType(InputType.TYPE_CLASS_NUMBER);
                cell.setBackground(null);
                cell.setText("0");
                row.addView(cell);
            }
            table.addView(row, new TableLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT));
        }
    }

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
            int [][] mat = new int[height][width];
            int k = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    mat[i][j] = Integer.parseInt(etArray.get(k).getText().toString());
                    k++;
                }
            }
            
            double result = Algorithms.determinantOfMatrix(mat, height);
            textViewDet.setText("Determinant: " + result);
            
        } else if (v == btnSole) {
            double [][] mat = new double[height][width];
            int k = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    mat[i][j] = Integer.parseInt(etArray.get(k).getText().toString());
                    k++;
                }
            }

            double[] x = new double[100];

            Algorithms.partialPivot(mat, height);
            Algorithms.backSubstitute(mat, height, x);

            TextView textView1 = view.findViewById(R.id.x1);
            TextView textView2 = view.findViewById(R.id.x2);
            TextView textView3 = view.findViewById(R.id.x3);
            TextView textView4 = view.findViewById(R.id.x4);
            TextView textView5 = view.findViewById(R.id.x5);
            TextView textView6 = view.findViewById(R.id.x6);
            TextView textView7 = view.findViewById(R.id.x7);

            HashMap<Integer, TextView> text_views = new HashMap<>();
            text_views.put(0, textView1);
            text_views.put(1, textView2);
            text_views.put(2, textView3);
            text_views.put(3, textView4);
            text_views.put(4, textView5);
            text_views.put(5, textView6);
            text_views.put(6, textView7);

            for (int i = 0; i < height; i++) {
                text_views.get(i).setText(Double.toString(x[i]));
            }

//            ArrayList<String> = slau();
        }
    }
}