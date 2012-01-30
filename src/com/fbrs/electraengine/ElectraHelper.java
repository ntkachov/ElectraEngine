package com.fbrs.electraengine;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

import android.content.Context;

public class ElectraHelper {
	
	public static String loadAsset(String name) throws IOException
	{
		BufferedReader reader = new BufferedReader(new InputStreamReader(new DataInputStream(ActivityEntry.a.getAssets().open(name))));
		String buffer = "";
		String line = "";
		while((line = reader.readLine()) != null){
			buffer += line + "\n";
		}
		return buffer;
	}

}
