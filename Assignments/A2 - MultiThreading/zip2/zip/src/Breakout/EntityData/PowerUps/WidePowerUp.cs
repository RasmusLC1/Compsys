using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using DIKUArcade.Math;
using System.IO;
using Breakout.BreakoutStates;
using System.Diagnostics;

namespace Breakout.EntityData.PowerUps {
    public class WidePowerUp : PowerUp {
        Image img = new Image (Path.Combine("Assets", "Images", "WidePowerUp.png"));
        private GameRunning gameRunning = GameRunning.GetInstance();
        private int value;
        Stopwatch stopwatch = new Stopwatch ();
        
        public WidePowerUp (DynamicShape shape, IBaseImage image) : base(shape, image) {
            Shape = shape;
            Image = img;
        }
        
        /// <summary>
        /// Starts a stopwatch and changes the player extent and sets the value to 1 so that specialEffects can become active
        /// Teleports the powerup away so it is no longer visible on the board
        /// </summary>
        public override void Effect () {
            stopwatch.Start();
            value = 1;
            this.Shape.Position = new Vec2F(100f,500f);
            gameRunning.GetPlayer.Shape.Extent = new Vec2F (0.32f, 0.03f);
        }

        /// <summary>
        /// Resets the player extent and deletes the powerup
        /// </summary>
        public override void SpecialEffect () {
            if (value == 1) {
                if (stopwatch.Elapsed.Seconds == 10) {
                    gameRunning.GetPlayer.Shape.Extent = new Vec2F (0.16f, 0.03f);
                    this.DeleteEntity ();
                }
            }
        }
    }
}