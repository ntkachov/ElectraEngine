package com.fbrs.electraengine;

import java.io.IOException;

import android.app.Activity;
import android.os.Bundle;
import android.view.Window;

public class ActivityEntry extends Activity {
	GL2JNIView mView;
	public static Activity a;
	@Override protected void onCreate(Bundle icicle) {
		super.onCreate(icicle);
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
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