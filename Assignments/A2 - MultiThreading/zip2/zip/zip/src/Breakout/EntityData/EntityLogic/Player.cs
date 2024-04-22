using DIKUArcade.Math;
using DIKUArcade.Entities;
using DIKUArcade.Graphics;

namespace Breakout.EntityData.EntityLogic {
    public class Player : Entity {
        private float moveLeft = 0.0f;
        private float moveRight = 0.0f;
        private float MOVEMENT_SPEED = 0.03f;
        private float BaseSpeed = 0.03f;
        public Vec2F GetPosition {
            get {return Shape.Position;}
        }
        public float GetMovementSpeed {
            get {return MOVEMENT_SPEED;}
        }

        public Player(DynamicShape shape, IBaseImage image): base(shape, image) {
            Shape = shape;
            Image = image;
        }

        /// <summary>
        /// Logic for moving if player hits a wall
        /// </summary>
        public void Move () {
            if ((moveLeft == -MOVEMENT_SPEED) && (Shape.Position.X > 0.0f)) {
                Shape.Move ();
            } else if ((moveRight == MOVEMENT_SPEED) && (Shape.Position.X < 0.98f - Shape.Extent.X)) {
                Shape.Move ();
            } 
        }

        /// <summary>
        /// MoveLeft logic, updates the direction according to new input
        /// </summary>
        /// <param name="val">boolean value to dertimine movement</param>
        public void SetMoveLeft (bool val) {
            if (val) {
                moveLeft -= MOVEMENT_SPEED;
                UpdateDirection ();
            } else {
                moveLeft = 0.0f;
                UpdateDirection ();
            }
        }

        /// <summary>
        /// MoveRight logic, updates the direction according to new input
        /// </summary>
        /// <param name="val">boolean value to dertimine movement</param>
        public void SetMoveRight(bool val) {
            if (val) {
                moveRight += MOVEMENT_SPEED;
                UpdateDirection();
            } else {
                moveRight = 0.0f;
                UpdateDirection();
            }
        }

        internal void IncrSpeed () {
            MOVEMENT_SPEED = BaseSpeed + 0.02f;
        }

        internal void DecrSpeed () {
            MOVEMENT_SPEED = BaseSpeed;
        }

        internal void ResetPosition () {
            Shape.Position = new Vec2F(0.45f, 0.05f);
        }
        
        /// <summary>
        /// Updates the direction on the player based on left, right, up and down direction
        /// </summary>
        private void UpdateDirection () {
            Shape.AsDynamicShape().Direction.X = moveRight + moveLeft;
        }
    }
}
