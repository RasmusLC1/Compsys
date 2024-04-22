using DIKUArcade.Graphics;
using DIKUArcade.Entities;
using System.IO;
using Breakout.Gameinfo;

namespace Breakout.EntityData.PowerUps {
    public class MoreTimePowerUp : PowerUp {
        Image img = new Image (Path.Combine("Assets", "Images", "pointImage.png"));
        private Timer timer = Timer.GetInstance();
        
        public MoreTimePowerUp (DynamicShape shape, IBaseImage image) : base(shape, image) {
            Shape = shape;
            Image = img;
        }

        /// <summary>
        /// Adds an addtional 30 seconds to the counter
        /// </summary>
        public override void Effect () {
            timer.AddTime(30);
            this.DeleteEntity();
        }

        public override void SpecialEffect() {}
    }
}