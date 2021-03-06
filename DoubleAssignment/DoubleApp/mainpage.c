/*! \mainpage My Personal Index Page
 *
 * \section objective_sec Objective
 *  
 *
 * The objective of this project is to create and IOS App to move the Double Robot using the localization services provided by Estimote Beacons and integrate 
 * the motion control with the Speech Recognition services provided by Bing Speech API and the Intent Detection provided by LUIS.ai. 
 *
 * \section accomplishment_sec Accomplishments
 * 
 * <ul>
 *      <li> Build a comprhensive user interface with:
 *      <ul>
 *          <li> buttons to:
 *          <ul>
 *              <li> enable/disable speech recognition
 *              <li> move the Double
 *              <li> enlongate/shorten the Double pole
 *              <li> deploy/retract the kickstands
 *          </ul>    
 *          <li> labels to show 
 *          <ul>
 *              <li> the state of the Speech Recognition(Enabled, Disabled, Listening)
 *              <li>speech recognition results: 
 *              <ul>
 *                  <li> phrases recognized with theris confidence level
 *                  <li> Intent with the highest score ad its score
 *                  <li> Type and values of the Entities relative to the Intent
 *              </ul>
 *              <li> Double position (x, y, orientation)
 *          </ul>
        </ul>
 *      <li> Commute vocal commands in something the Double is able to process
 *      <li> Move the Double toward a fixed goal position given by a vocal command
 *      <ul>
 *          <li> Double uses the goal position and its initial orientation to rotate toward the goal
 *          <li> Double moves toward the goal until the goal is within a certain range or the estimated travel time has elapsed (backup condition)
 *      </ul>
 *      <li> Make a test of the trigonometry calculations used to rotate the double toward the goal.
 *      <li> Disable the autonomous mode (stop the Double) whenever a button is pushed (security).   
 *      <li> Make the Double change its state (deploy/retract kickstands, elongate/shorten the pole) using vocal commands 
 *      <li> Make the Double recognize if it is in a certain range of a Beacon and act accordingly (Proximity Beacon)
 *      <li> Build Estimote locations using the coordinates of corner points and Beacons 
 * </ul>
 * 
 * \section limits_sec Limitations of the systems
 *  
 * <ul>
 *      <li> The code written to enable continous speech recognition works with iOS 8.3 while it doesn't with iOS 11
 *      <li> For the ipad, the only available location manager mode is the lite one:
 *      <ul>
 *          <li> position accuracy +/-2.62 m instead of +/-1 m
 *          <li> lower position update frequency
 *      </ul>    
 *      <li> Orientation for the ipad is available only for ios 9.0+
 *      <li> When building using the offiial app the orientation is counted clockwise from the y-axis; in order to make standard trigonometry calculations
 *           a manual map must be built with the orientation which goes from 0 on the x-axis and is counted from the x-axis to the y-axis.
 *      <li> Position given by the beacons fluctuates a lot and the accuracy is very poor
 *      <li> The App for semi-auto mapping the location has poor pefrormances, better use the location builder class
 *      <li> Double Control SDK has no documentation 
 *      <li> Nearables can be used only with the official app (no SDK yet)
 *      <li> Info from encoders not available, it could be because the firmware version of th Double is lower than 10
 *      (<a href="https://github.com/doublerobotics/Basic-Control-SDK-iOS/commit/5f1e5920d76ad5370d0cb6375aa379ac7c6b3e98)">DoubleControlSDK Commit</a>)
 *
 * </ul>
 *
 * \section arch_sec Software Architecture
 *
 * \subsection arch_scheme Architecture Scheme
 *
 *  <img src="architecture.jpg" style="width:50%">
 * 
 * \subsection arch_descr Architecture Description
 *
 *  After launching the app you can either control the Double Robot manually with the buttons on the interface or start the speech recognition by
 *  pushing the start rec green button.
 *  When the speech recognition is activated the registration are sent to the speech recognition server through webscoket connection and the result phrases
 *  are sent to the view controller and to the LUIS service. The LUIS service parses the the phrases and sends the highest scoring recognized intent with 
 *  relative entities to the view controller.
 *  If a intent: none is parsed the view controller should stop the microphone then send an adequate string to the vocal synthetizer.
 *  Else if a processable intent is detected it is translated into a command for the double. 
 *  For security the Double command buttons on the interface have higher priority then the autonomous mode, so whenever a command button is pushed the 
 *  Double stops whichever action it was doing.
 *  In the specific case a goToAction intent with a known entity of type room is detected, the double shold move autonomously toward the room fixed a priory position.
 *  In order to do this, the current position of the Double (x, y, orientation), published by Estimote localization each 0.2 seconds, is used to detrmine the
 *  movements the robot must perform.   
 *  The view controller is responsible for what the app does in the foreground, while the app delegate is responsible for the background behaviour.
 *  If the double gets close/far to/from a proximity beacon or viceversa, the app delegate sends an adequate string to the vocal synthetizer. 
 *  
 * \section sdkandtools_sec SDK and Tools
 *
 * <ul>
 *      <li> Xcode: an integrated development enviroment (IDE) for macOS containing a suite of software development tools
 *                  needed to develop iOS Apps
 *      <li> SpeechSDK: Bing Speech API cognitive services for speech recognition
 *      <li> Luis (Language Understanding Intelligent Service): extract the meaning of a phrase in a format which can be directly used in the code (JSON)
 *      <li> EstimoteProximitySDK: trigger actions when the distance of the device from a proximity beacon gets over/under a certain threshold
 *      <li> EstiomoteIndoorSDK: makes position(x, y, orientation) available to the device
 *      <li> EstimoteSDK
 *      <li> DoubleControlSDK
 *      <li> AVFoundation: speech synthetizer API 
 * </ul>
 *
 * \section howtorun_sec How to run
 * <ol>
 *      <li> iOS must be at least 11.0
 *      <li> check if the subscription key of the Bing Speech API is still valid, if this is not the case get a new one
 *      <li> USE THE WORKSPACE FILE (NOT THE PROJECT FILE) WHEN OPENING XCODE 
 *      <li> set IPHONE to 1 if you are using an iphone or set it to 0 if you are using an ipad
 *      <li> if you want to build a new rectangular map
 *           <ol> 
 *                <li> set MAP_FROM_CLOUD to 0
 *                <li> insert the coordinates of the corner points and of the loaction beacons in the section of the code
 *                     relative to the location builder 
 *                <li> run the code
 *                <li> substitue the location identifier with the one provided in the log
 *           </ol>
 *      <li> set MAP_FROM_CLOUD to 1 and set the location identifier of the desired location
 *      <li> download the App to your device
 *      <li> follow the instructions shown in the user interface
 * </ol>
 *
 * Remember from the limitation section that the coninuous behaviour of the speech recognition is not working from the moment ipad iOS was updated from 
 * version 8.3 to version 11.0 
 *
 * \section futuredev_sec Future Devevelopments
 * 
 * <ul>
 *      <li> find a way to re-enable the continous speech recognition behaviour, possible solutions are:    
 *      <ul>
 *          <li> Use a silence detector within the app to determine when to connect to the server to perform the speech recognition
 *          <li> Use the endMicandRecognition method before restarting the speech recognition (startMicAndRecognition method) after a final response is recieved. 
                 This could lead to a clean closure of the service before it restarts.   
 *          <li> Reinitialize the speech recognition client each time a final response is recieved
 *      </ul>
 *      <li> create a function to stop the micrphone before the double speaks and reactivate it afterwards in order to prevent it from looping on its own speech.
 *      <li> update the firmware of the Double to the version 10.0 to be able to get informations from the encoders and integrate them with the bluetooth positioning system. 
 *      <li> create a websocket connection between devices to share positions and develop a method to follow moving goals
 *      <li> develop the code to make the double search for a person (proximity beacon) in all the known rooms (goal positions), say hi if it finds the person or report back
             if it does not. (we began to develop the code but were not able to test it evan once so we didn't include the code in the project <a href="http://www.tommasoelia.com/ViewController.m">NotTestedCode</a> )
 *</ul>
 * \section appendix_sec Appendix
 *
 *  \subsection trig_sec Trigonometry
 
 *  <img src="trigonometry.png" style="width:50%">
 *  
 *  \subsection interface_sec User Interface
 *  
 *  <img src="interface.jpg" style="width:30%">
 *
 * \section biblio_sec Bibliography 
 * 
 * <a href="https://github.com/Azure-Samples/Cognitive-Speech-STT-iOS">SpeechRecognitionSDK</a>
 *
 * <a href="://www.luis.ai/welcome">LUIS</a>
 *
 * <a href="https://www.doublerobotics.com/double2.html">DoubleRobot</a>
 *
 * <a href="https://developer.apple.com/av-foundation/">AVFoundation</a>
 *
 * <a href="https://github.com/Estimote/iOS-Indoor-SDK">EstimoteIndoorLocationSDK</a>
 *
 * <a href="https://github.com/doublerobotics/Basic-Control-SDK-iOS">DoubleControlSDK</a>
 *
 * <a href="https://cocoapods.org/">cocoapods</a>
 *
 * <a href="https://developer.estimote.com/proximity/ios-tutorial/">EstimoteProximity</a>
 *
 *
 * 
 *
 *
 */
