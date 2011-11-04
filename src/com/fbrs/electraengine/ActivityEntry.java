package com.fbrs.electraengine;

import java.io.IOException;

import android.app.Activity;
import android.os.Bundle;

public class ActivityEntry extends Activity {
	GL2JNIView mView;
	public static Activity a;
	@Override protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);
		a = this;
		mView = new GL2JNIView(getApplication());
		
		setContentView(mView); 
		
	}

	@Override protected void onPause() {
		super.onPause();
		mView.onPause();
	}

	@Override protected void onResume() {
		super.onResume();
		mView.onResume();
	}
}