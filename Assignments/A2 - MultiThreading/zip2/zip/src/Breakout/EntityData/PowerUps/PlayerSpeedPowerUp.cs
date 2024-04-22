using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;
using Breakout.BreakoutStates;
using System.Diagnostics;

namespace Breakout.EntityData.PowerUps {
    public class PlayerSpeedPowerUp : PowerUp {
        Image img = new Image (Path.Combine("Assets", "Images", "SpeedPickUp.png"));
        private GameRunning gameRunning = GameRunning.GetInstance();
        private int value;
        Stopwatch stopwatch = new Stopwatch ();
        
        public PlayerSpeedPowerUp (DynamicShape shape, IBaseImage image) : base(shape, image) {
            Shape = shape;
            Image = img;
        }

        /// <summary>
        /// Starts a stopwatch and changes the players speed and sets the value to 1 so that specialEffects can become active
        /// Teleports the powerup away so it is no longer visible on the board
        /// </summary>
        public override void Effect () {
            stopwatch.Start();
            value = 1;
            this.Shape.Position = new Vec2F(100f,500f);
            gameRunning.GetPlayer.IncrSpeed();   
        }

        /// <summary>
        /// Deletes the powerup when time up and resets the player speed
        /// </summary>
        public override void SpecialEffect() {
            if (value == 1) {
                if (stopwatch.Elapsed.Seconds == 10) {
                    gameRunning.GetPlayer.DecrSpeed();
                    this.DeleteEntity();
                }
            }
        }
    }
}