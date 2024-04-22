using DIKUArcade.Graphics;
using DIKUArcade.Entities;

namespace Breakout.EntityData.Blocks {
    public class LeftDiagionalBlock : Block {
        private int hitpoints;
        private string Name;
        private float Speed = 0.005f;
        internal float startingpositionX;
        internal float startingpositionY;
        public override int GetHitpoints {
            get {return hitpoints;}
        }
        
        public LeftDiagionalBlock (StationaryShape shape, IBaseImage image, string name) : base(shape, image, name) {
            hitpoints = 1;
            Image = image;
            Name = name;
            startingpositionX = Shape.Position.X;
            startingpositionY = Shape.Position.Y;
        }

        public override void Hit (EntityContainer<Block> blocks) {
            hitpoints--;
            if (hitpoints == 0) {
                this.DeleteEntity();
            }
        }

        /// <summary>
        /// Moves the block on the X and Y axis Diagonally
        /// </summary> 
        /// <param name="speedmodifier">BallCount to keep speed stable</param>
        public override void Move (int speedmodifier) {
            Speed = Speed/speedmodifier;
            if (Shape.Position.Y-startingpositionY > 0.1  || Shape.Position.X-startingpositionX > 0.1) {
                Speed = Speed * -1;
            } else if (startingpositionY - Shape.Position.Y > 0.1 || startingpositionX - Shape.Position.X > 0.1) {
                Speed = Speed * -1;
            }
            Shape.Position.Y = Shape.Position.Y + Speed/speedmodifier;
            Shape.Position.X = Shape.Position.X + Speed/speedmodifier;
        }
    }
}