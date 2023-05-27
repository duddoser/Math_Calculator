package com.example.mathcalculator;

import android.os.Bundle;

import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.google.android.material.floatingactionbutton.FloatingActionButton;


public class MainFragment extends Fragment implements View.OnClickListener {
    private View view;
    private TextView text_view_output;
    private FloatingActionButton btn_matrix;

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
        return view;
    }

    @Override
    public void onClick(View v) {
        ((NavigationHost) getActivity()).navigateTo(new MatrixFragment(), true);
    }
}