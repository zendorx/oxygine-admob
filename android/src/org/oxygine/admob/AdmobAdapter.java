package org.oxygine.admob;

import android.app.Activity;
import android.util.Log;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.reward.RewardItem;
import com.google.android.gms.ads.reward.RewardedVideoAd;
import com.google.android.gms.ads.reward.RewardedVideoAdListener;

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

    public static int RW_ON_LOADED = 101;
    public static int RW_ON_OPENED = 102;
    public static int RW_ON_STARTED = 103;
    public static int RW_ON_CLOSED = 104;
    public static int RW_ON_REWARD = 105;
    public static int RW_ON_LEFT_APP = 106;
    public static int RW_ON_FAILED = 107;

    RewardedVideoAd mRewardedAd;

    public static native void onNativeChanged(int newStatus);
    public static native void onNativeRewardedChanged(int newStatus);

    public static native void onNativeReward(String type, int amount);
    public static native void onNativeRewardFailed(int i);

    public AdmobAdapter(Activity a, String INTERSTITIAL_UNIT_ID, String APP_ID, String testDeviceID) {
        _activity = a;
        _testDeviceID = testDeviceID;

        MobileAds.initialize(a, APP_ID);

        mInterstitialAd = new InterstitialAd(_activity);
        mInterstitialAd.setAdUnitId(INTERSTITIAL_UNIT_ID);

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


        if (!APP_ID.isEmpty())
        {
            mRewardedAd = MobileAds.getRewardedVideoAdInstance(_activity);

            mRewardedAd.setRewardedVideoAdListener(new RewardedVideoAdListener() {
                @Override
                public void onRewardedVideoAdLoaded() {
                    onNativeRewardedChanged(RW_ON_LOADED);
                }

                @Override
                public void onRewardedVideoAdOpened() {
                    onNativeRewardedChanged(RW_ON_OPENED);
                }

                @Override
                public void onRewardedVideoStarted() {
                    onNativeRewardedChanged(RW_ON_STARTED);
                }

                @Override
                public void onRewardedVideoAdClosed() {
                    onNativeRewardedChanged(RW_ON_CLOSED);
                }

                @Override
                public void onRewarded(RewardItem rewardItem) {

                    if (rewardItem == null)
                        onNativeReward("", 0);
                    else
                        onNativeReward(rewardItem.getType(), rewardItem.getAmount());
                }

                @Override
                public void onRewardedVideoAdLeftApplication() {
                    onNativeRewardedChanged(RW_ON_LEFT_APP);
                }

                @Override
                public void onRewardedVideoAdFailedToLoad(int i) {
                    onNativeRewardFailed(i);
                }
            });
        }

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



    /* REWARDED */


    public void loadRewarded(final String RW_UNIT_ID)
    {
        if (mRewardedAd == null)
        {
            Log.e(TAG, "Rewared video instance is null");
            return;
        }

        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AdRequest.Builder builder = new AdRequest.Builder();

                if (!_testDeviceID.isEmpty())
                    builder.addTestDevice(_testDeviceID);

                AdRequest adRequest = builder.build();
                mRewardedAd.loadAd(RW_UNIT_ID, adRequest);
            }
        });
    }

    public void showRewarded()
    {
        if (mRewardedAd == null)
        {
            Log.e(TAG, "Rewared video instance is null");
            return;
        }

        _activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (mRewardedAd.isLoaded())
                    mRewardedAd.show();
            }
        });
    }

    public boolean isRewardedLoaded()
    {
        if (mRewardedAd == null)
        {
            Log.e(TAG, "Rewared video instance is null");
            return false;
        }

        return mRewardedAd.isLoaded();
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