using DIKUArcade.Math;
using DIKUArcade.Entities;
using DIKUArcade.Graphics;

namespace Breakout.EntityData.EntityLogic {
    public class Ball : Entity {
        public Ball (DynamicShape shape, IBaseImage image) : base(shape, image) {
            Shape = shape;
            Image = image;
            Shape.AsDynamicShape().Direction = new Vec2F (0.011f, 0.011f);
        }

        /// <summary>
        /// Moves the ball entity from the 
        /// Given direction and changes direction
        /// if a wall is hit or deleted if it 
        /// hits bottom.
        /// </summary>
        public void Move () {
            Shape.AsDynamicShape().Move();
            if (Shape.Position.X < 0.00f) {
                Shape.AsDynamicShape().ChangeDirection(new Vec2F (
                    Shape.AsDynamicShape().Direction.X * -1.00f, 
                    Shape.AsDynamicShape().Direction.Y));
            } else if (Shape.Position.X > 1.00f - Shape.Extent.X) {   
                Shape.AsDynamicShape().ChangeDirection(new Vec2F (
                    Shape.AsDynamicShape().Direction.X * -1.00f, 
                    Shape.AsDynamicShape().Direction.Y));
            } else if (Shape.Position.Y < 0.00f) {
                this.DeleteEntity();
            } else if (Shape.Position.Y > 1.00f - Shape.Extent.X) {
                Shape.AsDynamicShape().ChangeDirection(new Vec2F (
                    Shape.AsDynamicShape().Direction.X, 
                    Shape.AsDynamicShape().Direction.Y * -1.00f));
            }
        }        
    }
}