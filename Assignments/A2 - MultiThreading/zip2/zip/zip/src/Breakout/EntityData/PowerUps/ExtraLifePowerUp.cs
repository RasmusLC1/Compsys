using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using System.IO;
using Breakout.Gameinfo;

namespace Breakout.EntityData.PowerUps {
    public class ExtraLifePowerUp : PowerUp {
        Image img = new Image (Path.Combine("Assets", "Images", "LifePickUp.png"));
        private GameValues values = GameValues.GetInstance();
        
        public ExtraLifePowerUp (DynamicShape shape, IBaseImage image) : base(shape, image) {
            Shape = shape;
            Image = img;
        }

        /// <summary>
        /// Adds an additional life to the player if current lives are below 5
        /// </summary>
        public override void Effect () {
            if (values.GetLives < 5) {
                values.AddLives();
            }
            this.DeleteEntity();
        }

        public override void SpecialEffect() {}
    }
}