package com.example.mathcalculator;

import android.app.AlertDialog;
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
import com.google.android.material.snackbar.Snackbar;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

public class MatrixFragment extends Fragment implements CustomDialogInterface, View.OnClickListener {
    private View view;
    private int height, width;
    private Button btnDeterminant, btnSole;
    private ArrayList<EditText> etArray = new ArrayList<>();
    private ArrayList<EditText> etArray2 = new ArrayList<>();
    private math math_object;

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
        math_object = new math();

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
                etArray.add(cell);
                cell.setBackground(null);
                cell.setText("0");
                row.addView(cell);
            }
            table.addView(row, new TableLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT));
        }

        TableLayout table2 = view.findViewById(R.id.table_layout_coefs);
        for (int i = 0; i < height; i++) {
            TableRow row = new TableRow(this.getContext());
            row.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT));
//                TextInputEditText cell = generateTextField();
            EditText cell = new EditText(this.getContext());
            etArray2.add(cell);
            cell.setBackground(null);
            cell.setText("0");
            row.addView(cell);
            table2.addView(row, new TableLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,
                    LinearLayout.LayoutParams.WRAP_CONTENT));
        }

    }

    @Override
    public void okButtonClicked(Pair<Integer, Integer> value) {
        height = (int) value.first;
        width = (int) value.second;
        generateMatrix();
    }

    @Override
    public void onClick(View v) {
        try {
            if (v == btnDeterminant) {
                TextView textViewDet = view.findViewById(R.id.tv_det_res);
                double [] mat = new double[height * width];
                for (int i = 0; i < height * width; i++) {
                    mat[i] = Double.parseDouble(etArray.get(i).getText().toString());
                }

//            double result = NdkManager.determinantOfMatrix(height, mat);
                double result = math_object.det(height, mat);
                new MaterialAlertDialogBuilder(this.getContext()).
                        setTitle("Determinant").
                        setMessage("Determinant of the matrix equals: " + result).
                        show();

            } else if (v == btnSole) {
                double[] mat = new double[height * width];
                for (int i = 0; i < height * width; i++) {
                    mat[i] = Double.parseDouble(etArray.get(i).getText().toString());
                }

                double[] B = new double[height];
                for (int i = 0; i < height; i++) {
                    B[i] = Double.parseDouble(etArray2.get(i).getText().toString());
                }

                ArrayList<TextView> eq_results = new ArrayList<>();
                for (int i = 1; i < height + 1; i++) {
                    String text_view_id = "x" + i;
                    eq_results.add(view.findViewById(getResources().getIdentifier(text_view_id,
                            "id", getActivity().getPackageName())));
                }

                Log.e("MATRIX AAAAAA", mat[0] + " " + mat[1] + " " + mat[2] + " " + mat[3]);
                Log.e("MATRIX BBBBBB", B[0] + " " + B[1]);

                String[] sole_result = math_object.slau(height, height, B, mat);
                for (int i = 0; i < height; i++) {
                    eq_results.get(i).setText(sole_result[i]);
                }

            }
        } catch (NumberFormatException nfe) {
            Snackbar.make(view, R.string.incorresct_input, Snackbar.LENGTH_SHORT).show();
        } catch (IndexOutOfBoundsException ioobe) {
            Snackbar.make(view, R.string.incorrect_determinant, Snackbar.LENGTH_SHORT).show();
        }
    }

}