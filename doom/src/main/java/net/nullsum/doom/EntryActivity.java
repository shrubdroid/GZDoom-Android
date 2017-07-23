package net.nullsum.doom;

import android.app.ActionBar;
import android.app.ActionBar.Tab;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v4.content.ContextCompat;
import android.support.v4.app.ActivityCompat;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MotionEvent;
import android.content.pm.PackageManager;
import static android.Manifest.*;

import net.nullsum.doom.AppSettings;
import net.nullsum.doom.OptionsFragment;
import net.nullsum.doom.Utils;
import com.beloko.touchcontrols.GamePadFragment;


public class EntryActivity extends FragmentActivity  {

    GamePadFragment gamePadFrag;

    /**
     * The serialization (saved instance state) Bundle key representing the
     * current tab position.
     */
    private static final int PERMISSIONS_REQUEST_WRITE_EXTERNAL_STORAGE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (ContextCompat.checkSelfPermission(this, permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{ permission.WRITE_EXTERNAL_STORAGE }, PERMISSIONS_REQUEST_WRITE_EXTERNAL_STORAGE);
        }

        setContentView(R.layout.activity_quake);

        final ActionBar actionBar = getActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

        AppSettings.reloadSettings(getApplication());

        GamePadFragment.gamepadActions = Utils.getGameGamepadConfig();

        actionBar.addTab(actionBar.newTab().setText("Gzdoom").setTabListener(new TabListener<LaunchFragmentGZdoom>(this, "Gzdoom", LaunchFragmentGZdoom.class)));
        actionBar.addTab(actionBar.newTab().setText("custom").setTabListener(new TabListener<CustomGameFragment>(this, "custom", CustomGameFragment.class)));
        actionBar.addTab(actionBar.newTab().setText("gamepad").setTabListener(new TabListener<GamePadFragment>(this, "gamepad", GamePadFragment.class)));
        actionBar.addTab(actionBar.newTab().setText("options").setTabListener(new TabListener<OptionsFragment>(this, "options", OptionsFragment.class)));


        actionBar.setSelectedNavigationItem(0);

        gamePadFrag = (GamePadFragment)getFragmentManager().findFragmentByTag("gamepad");

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        return true;
    }

    @Override
    public boolean onGenericMotionEvent(MotionEvent event) {
        if (gamePadFrag == null)
            gamePadFrag = (GamePadFragment)getFragmentManager().findFragmentByTag("gamepad");

        return gamePadFrag.onGenericMotionEvent(event);
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (gamePadFrag == null)
            gamePadFrag = (GamePadFragment)getFragmentManager().findFragmentByTag("gamepad");

        if (gamePadFrag.onKeyDown(keyCode, event))
            return true;
        else
            return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        if (gamePadFrag == null)
            gamePadFrag = (GamePadFragment)getFragmentManager().findFragmentByTag("gamepad");

        if ( gamePadFrag.onKeyUp(keyCode, event))
            return true;
        else
            return super.onKeyUp(keyCode, event);
    }

    public static class TabListener<T extends Fragment> implements ActionBar.TabListener {
        private final FragmentActivity mActivity;
        private final String mTag;
        private final Class<T> mClass;
        private final Bundle mArgs;
        private Fragment mFragment;

        public TabListener(FragmentActivity activity, String tag, Class<T> clz) {
            this(activity, tag, clz, null);
        }

        public TabListener(FragmentActivity activity, String tag, Class<T> clz, Bundle args) {
            mActivity = activity;
            mTag = tag;
            mClass = clz;
            mArgs = args;

            // Check to see if we already have a fragment for this tab, probably
            // from a previously saved state.  If so, deactivate it, because our
            // initial state is that a tab isn't shown.
            mFragment = mActivity.getFragmentManager().findFragmentByTag(mTag);

            if (mFragment == null) { //Actually create all fragments NOW
                mFragment = Fragment.instantiate(mActivity, mClass.getName(), mArgs);
                FragmentTransaction ft =  mActivity.getFragmentManager().beginTransaction();
                ft.add(android.R.id.content, mFragment, mTag);
                ft.commit();
            }

            if (mFragment != null && !mFragment.isHidden()) {
                FragmentTransaction ft = mActivity.getFragmentManager().beginTransaction();
                ft.hide(mFragment);
                ft.commit();
            }
        }

        public void onTabSelected(Tab tab, FragmentTransaction ft) {
            if (mFragment == null) {
                mFragment = Fragment.instantiate(mActivity, mClass.getName(), mArgs);
                ft.add(android.R.id.content, mFragment, mTag);
            } else {
                ft.show(mFragment);
            }
        }

        public void onTabUnselected(Tab tab, FragmentTransaction ft) {
            if (mFragment != null) {
                ft.hide(mFragment);
            }
        }

        public void onTabReselected(Tab tab, FragmentTransaction ft) {
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        switch (requestCode) {
            case PERMISSIONS_REQUEST_WRITE_EXTERNAL_STORAGE: {
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    // dirty hack :(
                    final ActionBar actionBar = getActionBar();
                    actionBar.setSelectedNavigationItem(1);
                    actionBar.setSelectedNavigationItem(0);
                }
            }
        }
    }

}
