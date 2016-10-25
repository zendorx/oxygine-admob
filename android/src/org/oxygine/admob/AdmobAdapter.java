package org.oxygine.admob;

import android.app.Activity;
import android.content.Intent;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.InterstitialAd;

import org.oxygine.lib.extension.ActivityObserver;

public class AdmobAdapter extends ActivityObserver
{
    private static String TAG = "AdmobAdapter";
    private Activity _activity;

    private String _testDeviceID;

    InterstitialAd mInterstitialAd;

    public static int ON_LOADED = 1;
    public static int ON_FAILED = 2;
    public static int ON_OPENED = 3;
    public static int ON_CLOSED = 4;


    public static native void onNativeChanged(int newStatus);

    public AdmobAdapter(Activity a, String UNIT_ID, String testDeviceID) {
        _activity = a;
        _testDeviceID = testDeviceID;

        mInterstitialAd = new InterstitialAd(_activity);
        mInterstitialAd.setAdUnitId(UNIT_ID);

        mInterstitialAd.setAdListener(new AdListener() {

            @Override
            public void onAdClosed() {
                onNativeChanged(ON_CLOSED);
            }

            @Override
            public void onAdFailedToLoad(int errorCode) {
                onNativeChanged(ON_FAILED);
            }

            @Override
            public void onAdLeftApplication() {
            }

            @Override
            public void onAdOpened() {
                onNativeChanged(ON_OPENED);
            }

            @Override
            public void onAdLoaded() {
                onNativeChanged(ON_LOADED);
            }
        });


    }

    public boolean isLoaded()
    {
        return mInterstitialAd.isLoaded();
    }

    public void show()
    {
        if (!isLoaded())
            return;

        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                mInterstitialAd.show();
            }
        });
    }

    public void load()
    {
        if (isLoaded())
            return;

        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AdRequest.Builder builder = new AdRequest.Builder();
                if (!_testDeviceID.isEmpty())
                    builder.addTestDevice(_testDeviceID);

                AdRequest adRequest = builder.build();
                mInterstitialAd.loadAd(adRequest);
            }
        });
    }

    /*@Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {

    }

    @Override
    public void onDestroy() {
    }

    @Override
    public void onResume() {
    }

    @Override
    public void onPause() {

    }*/
}