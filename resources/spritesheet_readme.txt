Sprite Sheets Readme: 


When you want to create an AnimatedSprite, you have two options...Using a bunch of separate image files, or use a sprite sheet. There is a separate constructor for both options. To create an AnimatedSprite using a sprite sheet, use the constructor: 

AnimatedSprite::AnimatedSprite(string id, string spritesheet, string xml);

Each sprite sheet must be a .png file, and must have an associated xml file. 
The xml file tells the game where each frame of the animation is located on the sheet. It has a very particular format, which looks like: 

    <sprite n="dash_right-0.png" x="1" y="1" w="32" h="32"/>
    <sprite n="dash_right-1.png" x="35" y="1" w="32" h="32"/>
    <sprite n="dash_right-2.png" x="69" y="1" w="32" h="32"/>
    <sprite n="dash_right-3.png" x="103" y="1" w="32" h="32"/>
    <sprite n="dash_right-4.png" x="137" y="1" w="32" h="32"/>

These MUST begin on line 23 of the xml file (this is how TexturePacker automatically generates it. The lines above 23 are just explanatory stuff.) 

You can see that each line contains the name and frame number of a particular animation (e.g. "dash_right-1" or "idle-right-5"). This lets you have multiple animations on a single sprite sheet. 

In order to add an animation to an AnimatedSprite object, you must use the function: 

AnimatedSprite::addAnimationFromSpriteSheet(string texture, string animName, int numFrames, int frameRate, bool loop);

Here, the first parameter is the entire sprite sheet png, and everything else is essentially the same as the old addAnimation() function. 

This is where it becomes essential that you make sure you have the name of the animation in the proper format in the xml file. Otherwise, the engine won't be able to load it. So, if you have an "idle" animation, a "jump" animation, a "walk" animation, etc, the xml file must look exactly like above. (Also see the "player_sprites.xml" file for a full example). 

Since most sprite sheets downloaded from an online source don't have a xml file included with them, you have to create one using TexturePacker. (If they do have an included xml file, you need to make sure you put it in the format above.) To use TexturePacker, you first need to separate each individual frame. (I found that this online sprite cutter at "https://ezgif.com/sprite-cutter" works great.) Then you select all the frames, and just drag them into TexturePacker, and it will do the rest. You'll need to either edit the file names to reflect the name of the animation ("Walk", "jump", etc) before you import to TexturePacker, or you can manually edit the XML when you're done. 

myGame is currently running by using the "idle_right" animation from the "player_animations.png" sprite sheet in the player folder, so see that for a good example. 






