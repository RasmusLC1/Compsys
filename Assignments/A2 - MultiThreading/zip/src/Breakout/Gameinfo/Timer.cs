using DIKUArcade.Timers;
using System;
using Breakout.Levels;

namespace Breakout.Gameinfo {
    public class Timer {
        private Meta meta = new Meta();
        private static Timer instance = null;
        private int seconds;
        private int TimeLeft;
        private static int AddSec;
        public int GetTime {
            get {return TimeLeft;}
        }

        /// <summary>
        /// Sets the instance so there will only ever be one active timer running
        /// </summary>
        /// <returns>Timer instance</returns>
        public static Timer GetInstance() {
            if (Timer.instance == null) {
                Timer.instance = new Timer();
            }
            return Timer.instance;
        }

        /// <summary>
        /// Starts the timer based on the level timer value
        /// </summary>
        /// <param name="fileName">level name</param>
        /// <returns>total seconds to complete level</returns>
        public int StartTimer(string fileName) {
            TimeLeft = -5;
            AddSec = 0;
            DIKUArcade.Timers.StaticTimer.RestartTimer();
            seconds = meta.MetaReaderTimer(fileName);
            return seconds;
        }

        /// <summary>
        /// Updates the time by subtracting additionalseconds + the total amount of seconds
        /// from the time that has already elapsed using a staticTimer
        /// </summary>
        /// <returns>current time left</returns>
        public int UpdateTime () {
            if (seconds > 0) {
                int CurrentTime = Convert.ToInt32(StaticTimer.GetElapsedSeconds());
                TimeLeft = AddSec + seconds - CurrentTime;
            }
            return TimeLeft;
        }
        
        /// <summary>
        /// Adds extra time to the timer
        /// </summary>
        /// <param name="Sec">extra time in seconds</param>
        public void AddTime (int Sec) {
            AddSec = AddSec + Sec;
        }
    }
}