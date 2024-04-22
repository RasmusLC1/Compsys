using System;
namespace Breakout.BreakoutStates {
    public class StateTransformer {
        
        /// <summary>
        /// Transforms a string into a correlating GameStateType
        /// </summary>
        /// <param name="state">the string argument</param>
        /// <returns>A GameStateType</returns>
        public static GameStateType TransformStringToState (string state) {
            switch(state) {
                case ("GAME_RUNNING"):
                    return GameStateType.GameRunning;
                case ("MAIN_MENU"):
                    return GameStateType.MainMenu;
                case ("LEVEL_MENU"): 
                    return GameStateType.LevelMenu;
                case ("GAME_PAUSED"):
                    return GameStateType.GamePaused;
                case ("GAMELOST"):
                    return GameStateType.GameLost;
                case ("GAMEWON"):
                    return GameStateType.GameWon;
                default:
                    throw new ArgumentException ("string does not correspond to a GameStateType");
            }   
        }
    }
}