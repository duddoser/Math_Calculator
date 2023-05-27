package com.example.mathcalculator;

import android.os.Bundle;

import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;

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

public class MatrixFragment extends Fragment implements CustomDialogInterface, View.OnClickListener {
    private View view;
    private int height, width;
    private Button btnDeterminant, btnSole;

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
            textViewDet.setText("Determinant: ");
        }
    }
}