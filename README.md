# SaveLoadGameSystem
Unreal Engine 5 (UE5) Simple Save/Load Subsystem derived from Game Instance.

**Welcome to my simple Save and Load Game System built specifically for Unreal Engine.**

This version is safe to use with Unreal Engine version 5.6.1, but you are free to experiment with other versions.

If you are going to use these files directly, make sure that you keep their names intact, as there are some direct references within the GameMode constructor (**DefaultPlayerController** and **ExtraDefaultPawn**).

In case you desire to change the class names, all you have to do is change the references within these classes:

- **DefaultPlayerController.h** -> Is referencing SaveLoadGameInterface.
- **DefaultGameInstance.h** -> Is referencing SaveLoadGameSubsystem.
- **DefaultGameMode.h** -> Is referencing SaveLoadGameInterface, SaveLoadGameSubsystem, DefaultGameInstance, ExtraDefaultPawn, DefaultPlayerController.
- **SaveLoadGameSubsystem.cpp** -> Is referencing DefaultSaveGame.

**About the SaveLoadGameSubsystem:**

This Save/Load System is meant to simplify the implementation of a Save Game/Load Game feature within one's project. All the code is written in C++, whilst most visuals like Player Data (player name, player level, player score, etc.) are meant to be sent to Widgets.

The current setup easily allows for certain functions to be called from any Blueprint Class, namely:

- **SetPlayerName**;
- **HandleAutoSave_Sync**;
- **HandleLoad_Sync**;

Most other functions are pure C++ and are not meant to be called from any Blueprint environment, but you are free to adjust and amplify anything to the project's needs.

Note that there is an interface, SaveLoadGameInterface, that is strictly meant for the C++ environment, never to be used in Blueprints. The reason for this is simply to keep things from overlapping each other (imagine having a BP Interface that does the same thing or something similar) and for simplicity's sake (easier to debug, adapt and expand). You run the risk of breaking some of the code if you try to, so make sure to create a new interface if you want to add other functionalities or expand the current existing one whilst keeping it purely C++ focused.

Most functions and variables are commented, so do check on them in case you're not fully understanding what something is for.

I'm open to suggestions as to how this project can be improved, so make sure to leave a comment in case you've mingled with any code.

I hope that this small project can help anyone better understand how C++ works (in case you're new) and to cut some time in creating a Save/Load System.

Note that this project is meant to improve over time, so make sure to check regularly (or not).

-CranchyDev
