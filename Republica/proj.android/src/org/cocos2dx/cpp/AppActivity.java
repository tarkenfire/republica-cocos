/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;







import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.games.Games;
import com.google.example.games.basegameutils.GameHelper;
import com.google.example.games.basegameutils.GameHelper.GameHelperListener;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class AppActivity extends Cocos2dxActivity {
	
	private static Activity selfRef = null;
	private static GoogleApiClient clientRef = null;
	GameHelper mHelper;
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		//static refs for game lib callings
		AppActivity.selfRef = this;

		//create helper
		mHelper = new GameHelper(this, GameHelper.CLIENT_GAMES);

	    GameHelperListener listener = new GameHelper.GameHelperListener() {
	        @Override
	        public void onSignInSucceeded() {
	            // handle sign-in succeess
	        	AppActivity.clientRef = mHelper.getApiClient();
	        }
	        @Override
	        public void onSignInFailed() {
	            // handle sign-in failure (e.g. show Sign In button)
	        }

	    };
	    mHelper.setup(listener);
	}
	
	@Override
	protected void onStart() 
	{
	    super.onStart();
	    mHelper.onStart(this);
	}

	@Override
	protected void onStop() 
	{
	    super.onStop();
	    mHelper.onStop();
	}

	@Override
	protected void onActivityResult(int request, int response, Intent data) 
	{
	    super.onActivityResult(request, response, data);
	    mHelper.onActivityResult(request, response, data);
	}

	//methods called from C++
	public static void launchShareIntent(String text)
	{
		Intent sendIntent = new Intent();
		sendIntent.setAction(Intent.ACTION_SEND);
		sendIntent.putExtra(Intent.EXTRA_TEXT, text);
		sendIntent.setType("text/plain");
		selfRef.startActivity(sendIntent);
	}
	
	public static void unlockAchievement(String id)
	{
		Games.Achievements.unlock(clientRef, id);
	}
	
	public static void showAchievements()
	{
		Intent sender = Games.Achievements.getAchievementsIntent(clientRef);
		selfRef.startActivityForResult(sender, 0);
	}
}
