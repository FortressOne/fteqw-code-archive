package com.fteqw;
import android.view.inputmethod.InputMethodManager;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.InputDevice;
import android.view.WindowManager;

public class FTENativeActivity extends android.app.Activity
{
	private static native void keypress(int devid, boolean down, int androidkey, int unicode);
	private static native void mousepress(int devid, int buttonbits);
	private static native void motion(int devid, int action, float x, float y, float z, float size);
	private static native boolean wantrelative();
	private static native void axis(int devid, int axisid, float value);
	static
	{
		System.loadLibrary("ftedroid");
	}

	//called by C code on errors / quitting.
	public void showMessageAndQuit(String errormessage)
	{
		final android.app.Activity act = this;
		final String errormsg = errormessage;
		if (errormsg.equals(""))
		{	//just quit
			finish();
			System.exit(0);
		}
		else runOnUiThread(new Runnable()
		{	//show an error message, then quit.
			public void run()
			{
//				act.getView().setVisibility(android.view.View.GONE);
				android.app.AlertDialog ad = new android.app.AlertDialog.Builder(act).create();
				ad.setTitle("Fatal Error");
				ad.setMessage(errormsg);
				ad.setCancelable(false);
				ad.setButton("Ok", new android.content.DialogInterface.OnClickListener()
				{
					public void onClick(android.content.DialogInterface dialog, int which)
					{
						finish();
						System.exit(0);
					}
				});
				ad.show();
			}
		});
	}
	public void updateScreenKeepOn(final boolean keepon)
	{
		final android.app.Activity act = this;
		runOnUiThread(new Runnable()
		{
			public void run()
			{
				if (keepon)
					act.getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
				else
					act.getWindow().setFlags(0, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
			}
		});
	}


	//called by C code to set orientation.
	public void updateOrientation(String orientation)
	{
		final String ors = orientation;
		runOnUiThread(new Runnable()
		{
			public void run()
			{
				int ori = android.content.pm.ActivityInfo.SCREEN_ORIENTATION_SENSOR;
				if (ors.equalsIgnoreCase("unspecified"))
					ori = android.content.pm.ActivityInfo.SCREEN_ORIENTATION_UNSPECIFIED;
				else if (ors.equalsIgnoreCase("landscape"))
					ori = android.content.pm.ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;
				else if (ors.equalsIgnoreCase("portrait"))
					ori = android.content.pm.ActivityInfo.SCREEN_ORIENTATION_PORTRAIT;
				else if (ors.equalsIgnoreCase("user"))
					ori = android.content.pm.ActivityInfo.SCREEN_ORIENTATION_USER;
				else if (ors.equalsIgnoreCase("behind"))
					ori = android.content.pm.ActivityInfo.SCREEN_ORIENTATION_BEHIND;
				else if (ors.equalsIgnoreCase("sensor"))
					ori = android.content.pm.ActivityInfo.SCREEN_ORIENTATION_SENSOR;
				else if (ors.equalsIgnoreCase("nosensor"))
					ori = android.content.pm.ActivityInfo.SCREEN_ORIENTATION_NOSENSOR;
				//the following are api level 9+
				else if (ors.equalsIgnoreCase("sensorlandscape"))
					ori = 6;//android.content.pm.ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE;
				else if (ors.equalsIgnoreCase("sensorportrait"))
					ori = 7;//android.content.pm.ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT;
				else if (ors.equalsIgnoreCase("reverselandscape"))
					ori = 8;//android.content.pm.ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE;
				else if (ors.equalsIgnoreCase("reverseportrait"))
					ori = 9;//android.content.pm.ActivityInfo.SCREEN_ORIENTATION_REVERSE_PORTRAIT;
				else if (ors.equalsIgnoreCase("fullsensor"))
					ori = 10;//android.content.pm.ActivityInfo.SCREEN_ORIENTATION_FULL_SENSOR;
				//and the default, because specifying it again is always useless.
				else
					ori = android.content.pm.ActivityInfo.SCREEN_ORIENTATION_SENSOR;
				android.util.Log.i("FTEDroid", "Orientation changed to " + ori + " (" + ors + ").");
				setRequestedOrientation(ori);
			}
		});
	};


	//keyboard stuff, called from C.
	public void showKeyboard(int softkeyflags)
	{	//needed because the ndk's ANativeActivity_showSoftInput is defective
		final android.app.Activity act = this;
		final int flags = softkeyflags;
		runOnUiThread(new Runnable()
		{
			public void run()
			{
				if (flags != 0)
				{
					InputMethodManager imm = (InputMethodManager)getSystemService(android.content.Context.INPUT_METHOD_SERVICE);
					imm.showSoftInput(act.getWindow().getDecorView(), InputMethodManager.SHOW_FORCED);
				}
				else
				{
					InputMethodManager imm = (InputMethodManager)getSystemService(android.content.Context.INPUT_METHOD_SERVICE);
					imm.hideSoftInputFromWindow(act.getWindow().getDecorView().getWindowToken(), 0);
				}
			}
		});
	}

	@Override
	protected void onCreate(android.os.Bundle savedInstanceState)
	{
		mIMM = getSystemService(InputMethodManager.class);
		getWindow().takeSurface(this);
		getWindow().setFormat(PixelFormat.RGB_565);
		getWindow().setSoftInputMode(
				WindowManager.LayoutParams.SOFT_INPUT_STATE_UNSPECIFIED
				| WindowManager.LayoutParams.SOFT_INPUT_ADJUST_RESIZE);
		mNativeContentView = new NativeContentView(this);
		mNativeContentView.mActivity = this;
		setContentView(mNativeContentView);
		mNativeContentView.requestFocus();
		mNativeContentView.getViewTreeObserver().addOnGlobalLayoutListener(this);

		byte[] nativeSavedState = savedInstanceState != null
			? savedInstanceState.getByteArray(KEY_NATIVE_SAVED_STATE) : null;
		mNativeHandle = loadNativeCode(path, funcname, Looper.myQueue(),
				getAbsolutePath(getFilesDir()), getAbsolutePath(getObbDir()),
				getAbsolutePath(getExternalFilesDir(null)),
				Build.VERSION.SDK_INT, getAssets(), nativeSavedState,
				classLoader, classLoader.getLdLibraryPath());

		super.onCreate(savedInstanceState);
	}

	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		int act = event.getAction();
		if (act == KeyEvent.ACTION_DOWN)
		{
			int metastate = event.getMetaState();
			int unichar = event.getUnicodeChar(metastate);
			if (unichar == 0)
				unichar = event.getUnicodeChar();
			if (unichar == 0)
				unichar = event.getDisplayLabel();

			keypress(event.getDeviceId(), true, event.getKeyCode(), unichar);
			return true;
		}
		else if (act == KeyEvent.ACTION_UP)
		{
			keypress(event.getDeviceId(), false, event.getKeyCode(), 0);
			return true;
		}
		else
			android.util.Log.i("FTEDroid", "other type of event");
		//ignore ACTION_MULTIPLE or whatever it is, apparently its deprecated anyway.

		return super.dispatchKeyEvent(event);
	}

	private static boolean canrelative;
	private static int AXIS_RELATIVE_X;//MotionEvent 24
	private static int AXIS_RELATIVE_Y;//MotionEvent 24
	private static java.lang.reflect.Method MotionEvent_getAxisValueP; //MotionEvent 12
	private static int SOURCE_MOUSE;	//InputDevice
	private static boolean canbuttons;
	private static java.lang.reflect.Method MotionEvent_getButtonState; //MotionEvent 14

	private static boolean canjoystick;
	private static java.lang.reflect.Method MotionEvent_getAxisValueJ;
	private static java.lang.reflect.Method InputDevice_getMotionRange;
	private static int SOURCE_JOYSTICK; //InputDevice
	private static int AXIS_X;
	private static int AXIS_Y;
	private static int AXIS_LTRIGGER;
	private static int AXIS_Z;
	private static int AXIS_RZ;
	private static int AXIS_RTRIGGER;
	static
	{
		//if (android.os.Build.VERSION.SDK_INT >= 12)
		try
		{
			MotionEvent_getAxisValueP = MotionEvent.class.getMethod("getAxisValue", int.class, int.class); //api12
			java.lang.reflect.Field relX = MotionEvent.class.getField("AXIS_RELATIVE_X");	//api24ish
			java.lang.reflect.Field relY = MotionEvent.class.getField("AXIS_RELATIVE_Y");	//api24ish
			AXIS_RELATIVE_X = (Integer)relX.get(null);
			AXIS_RELATIVE_Y = (Integer)relY.get(null);
			SOURCE_MOUSE = (Integer)InputDevice.class.getField("SOURCE_MOUSE").get(null);
			canrelative = true;	//yay, no exceptions.
			android.util.Log.i("FTEDroid", "relative mouse supported");

			MotionEvent_getButtonState = MotionEvent.class.getMethod("getButtonState");
			canbuttons = true;
			android.util.Log.i("FTEDroid", "mouse buttons supported");
		} catch(Exception e) {
			canrelative = false;
			android.util.Log.i("FTEDroid", "relative mouse not supported");
		}
		try
		{
			MotionEvent_getAxisValueJ = MotionEvent.class.getMethod("getAxisValue", int.class); //api12
			InputDevice_getMotionRange = InputDevice.class.getMethod("getMotionRange", int.class); //api12
			AXIS_X = (Integer)MotionEvent.class.getField("AXIS_X").get(null);
			AXIS_Y = (Integer)MotionEvent.class.getField("AXIS_Y").get(null);
			AXIS_LTRIGGER = (Integer)MotionEvent.class.getField("AXIS_LTRIGGER").get(null);
			AXIS_Z = (Integer)MotionEvent.class.getField("AXIS_Z").get(null);
			AXIS_RZ = (Integer)MotionEvent.class.getField("AXIS_RZ").get(null);
			AXIS_RTRIGGER = (Integer)MotionEvent.class.getField("AXIS_RTRIGGER").get(null);
			SOURCE_JOYSTICK = (Integer)InputDevice.class.getField("SOURCE_JOYSTICK").get(null);
			canjoystick = true;
			android.util.Log.i("FTEDroid", "gamepad supported");
		} catch(Exception e) {
			canjoystick = false;
			android.util.Log.i("FTEDroid", "gamepad not supported");
		}
	}
	private static void handleJoystickAxis(MotionEvent event, InputDevice dev, int aaxis, int qaxis)
	{
		try
		{
			final InputDevice.MotionRange range = (InputDevice.MotionRange)InputDevice_getMotionRange.invoke(dev, aaxis, event.getSource());
			if (range != null)
			{
				final float flat = range.getFlat();
				float v = (Float)MotionEvent_getAxisValueJ.invoke(event, aaxis, 0);
				if (Math.abs(v) < flat)
					v = 0;	//read as 0 if its within the deadzone.
				axis(event.getDeviceId(), qaxis, v);
			}
		}
		catch(Exception e)
		{
		}
	}
	private boolean motionEvent(MotionEvent event)
	{
		int id;
		float x, y, size;
		final int act = event.getAction();

		//handle gamepad axis
		if ((event.getSource() & SOURCE_JOYSTICK)!=0 && event.getAction() == MotionEvent.ACTION_MOVE)
		{
			InputDevice dev = event.getDevice();
			handleJoystickAxis(event, dev, AXIS_X, 0);
			handleJoystickAxis(event, dev, AXIS_Y, 1);
			handleJoystickAxis(event, dev, AXIS_LTRIGGER, 2);
			
			handleJoystickAxis(event, dev, AXIS_Z, 3);
			handleJoystickAxis(event, dev, AXIS_RZ, 4);
			handleJoystickAxis(event, dev, AXIS_RTRIGGER, 5);

			return true;
		}

		final int pointerCount = event.getPointerCount();
		int i;
		for (i = 0; i < pointerCount; i++)
		{
			if (canrelative && event.getSource() == SOURCE_MOUSE && wantrelative())
			{
				try
				{
					x = (Float)MotionEvent_getAxisValueP.invoke(event, AXIS_RELATIVE_X, i);
					y = (Float)MotionEvent_getAxisValueP.invoke(event, AXIS_RELATIVE_Y, i);
					motion(event.getPointerId(i), 1, x, y, 0, event.getSize(i));
				}
				catch(Exception e)
				{
					android.util.Log.i("FTEDroid", "exception using relative mouse");
					canrelative=false;
				}
			}
			else
			{
				motion(event.getPointerId(i), 0, event.getX(i), event.getY(i), 0, event.getSize(i));
			}
		}

		switch(act & event.ACTION_MASK)
		{
		case MotionEvent.ACTION_DOWN:
		case MotionEvent.ACTION_POINTER_DOWN:
			id = ((act&event.ACTION_POINTER_ID_MASK) >> event.ACTION_POINTER_ID_SHIFT);
			x = event.getX(id);
			y = event.getY(id);
			size = event.getSize(id);
			id = event.getPointerId(id);
			if (canbuttons)
			{
				try {mousepress(id, (Integer)MotionEvent_getButtonState.invoke(event));}
				catch(Exception e){}
			}
			else
				motion(id, 2, x, y, 0, size);
			break;
		case MotionEvent.ACTION_UP:
		case MotionEvent.ACTION_POINTER_UP:
			id = ((act&event.ACTION_POINTER_ID_MASK) >> event.ACTION_POINTER_ID_SHIFT);
			x = event.getX(id);
			y = event.getY(id);
			size = event.getSize(id);
			id = event.getPointerId(id);
			if (canbuttons)
			{
				try {mousepress(id, (Integer)MotionEvent_getButtonState.invoke(event));}
				catch(Exception e){}
			}
			else
				motion(id, 3, x, y, 0, size);
			break;
		case MotionEvent.ACTION_MOVE:
			break;
		default:
			return false;
		}
		return true;
	}

	@Override
	public boolean dispatchTouchEvent(MotionEvent event)
	{	//works when mouse is pressed...
		return motionEvent(event);
	}
//	@Override
	public boolean dispatchGenericMotionEvent(MotionEvent event)
	{	//works even when mouse is not pressed
		return motionEvent(event);
	}


	//launching stuff
	/*private static native int unicodeKeyPress(int unicode);
	@Override
	void onNewIntent(Intent intent)
	{
		super.onNewIntent(intent);
	}*/
}
