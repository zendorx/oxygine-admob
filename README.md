# oxygine-admob instructions

1. Go to your projects folder and clone repository

> git clone https://github.com/zendorx/oxygine-admob 

Your folder structure should look like this:

> /your_projects/
> 	myproject
>	oxygine-framework
>	oxgine-admob
>	SDL


2. Go to Android.mk file and add follow lines

> LOCAL_STATIC_LIBRARIES := \
> 	...
>	oxygine_admob-static \


...

> $(call import-module, oxygine-admob) 



3. Go to settings.gradle file and add

> include 'oxygine-admob'
> project(':oxygine-admob').projectDir = new File('../../../..//oxygine-admob/android')


4. In the gradle.build file add line into dependencies block

>dependencies {
>	...
>	compile("oxygine-admob")

5. Next step it is initialize library in the java code, go to your MainActivity.java and add next lines:

> import org.oxygine.admob
...



> @Override
>    protected void onCreate(Bundle savedInstanceState)
>    {
>       String testDeviceID = "";//Enter device id for tests
>	  	addObserver(new AdmobAdapter(this, "YOUR_INTERSTITIAL_UNIT_ID", "YOUR_APP_ID", testDeviceID));


6. Finally include lib in your cmake file like this:

>add_subdirectory(../../oxygine-admob oxygine-admob)
>include_directories(${OXYGINE_ADMOB_INCLUDE_DIRS})