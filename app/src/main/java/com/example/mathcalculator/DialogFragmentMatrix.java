package com.example.mathcalculator;

import android.app.Dialog;
import android.content.DialogInterface;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.EditText;
import android.widget.LinearLayout;

public class DialogFragmentMatrix extends DialogFragment {
    private View view;
    private MatrixFragment matrixFragment;
    private CustomDialogInterface customDialogInterface;

    public DialogFragmentMatrix() {
        // Required empty public constructor
    }

    public DialogFragmentMatrix(CustomDialogInterface customDialogInterface) {
        this.customDialogInterface = customDialogInterface;
    }


    public static DialogFragmentMatrix newInstance(String param1, String param2) {
        DialogFragmentMatrix fragment = new DialogFragmentMatrix();
        Bundle args = new Bundle();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        view = getActivity().getLayoutInflater().inflate(R.layout.fragment_dialog,
                new LinearLayout(getActivity()), false);
        view.setBackgroundColor(getResources().getColor(R.color.background));

        Dialog builder = new Dialog(getActivity());
        builder.requestWindowFeature(Window.FEATURE_NO_TITLE);
        builder.getWindow().setBackgroundDrawable(new ColorDrawable(android.
                graphics.Color.TRANSPARENT));
        builder.setContentView(view);

        return builder;
    }

    @Override
    public void onDismiss(@NonNull DialogInterface dialog) {
        super.onDismiss(dialog);
        EditText h = (EditText) view.findViewById(R.id.ed_height);
        int height = Integer.parseInt(h.getText().toString());

        EditText w = (EditText) view.findViewById(R.id.ed_width);
        int width = Integer.parseInt(w.getText().toString());

        Pair<Integer, Integer> pair = new Pair<>(height, width);
        dialog.dismiss();
        customDialogInterface.okButtonClicked(pair);
    }

    void setCustomDialogInterface(CustomDialogInterface customDialogInterface) {
        this.customDialogInterface = customDialogInterface;
    }
}