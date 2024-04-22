namespace Breakout.Gameinfo {
    public class GameChecker {
        
        /// <summary>
        /// Checks if the Game is over or if player needs a new ball
        /// </summary>
        /// <param name="lives">Player lives</param>
        /// <param name="time">remaining time</param>
        /// <param name="ballCount">current amount of balls in play</param>
        /// <returns>int value corresponding to GameState in GameRunning</returns>
        public int GameOver (int lives, int time, int ballCount) {
            if (ballCount == 0) {
                return 2;
            } else if (lives == 0 || time == 0) {
                return 0;
            } 
            return 1;
        }
    }
}