using DIKUArcade.Math;
using DIKUArcade.Entities;
using DIKUArcade.Physics;
using System;
using Breakout.EntityData.Blocks;
using Breakout.EntityData.PowerUps;
using Breakout.Gameinfo;

namespace Breakout.EntityData.EntityLogic {
    public class BallHitDetection {
        private GameValues values = GameValues.GetInstance();

        /// <summary>
        /// Hitdetection logic. Detects the direction the ball comes from and what it has hit
        /// and sends out a value depending on this information and calls Effectshit method if
        /// block is hit. Looks for if a block is a PowerUp and then triggers the PowerUp that shares
        /// its location
        /// </summary>
        /// <param name="balls">balls currently loaded</param>
        /// <param name="blocks">Blocks currently loaded</param>
        /// <param name="powerUps">powerUps currently loaded</param>
        /// <param name="player">player currently loaded</param>
        public void HitDetection(EntityContainer <Ball> balls, EntityContainer<Block> blocks,
        EntityContainer<PowerUp> powerUps, Player player) {
            balls.Iterate(ball => {
                ball.Move();
                if (CollisionDetection.Aabb(ball.Shape.AsDynamicShape(), player.Shape).Collision) {
                    ball.Shape.AsDynamicShape().ChangeDirection(new Vec2F (
                        ball.Shape.AsDynamicShape().Direction.X, 
                        ball.Shape.AsDynamicShape().Direction.Y * -1.00f));
                }
                blocks.Iterate (block => {
                    block.Move (balls.CountEntities ());
                    if (CollisionDetection.Aabb(ball.Shape.AsDynamicShape(), block.Shape).Collision) {
                        if (block.Shape.Position.Y + block.Shape.Extent.Y <= ball.Shape.Position.Y ||
                            block.Shape.Position.Y >= ball.Shape.Position.Y + ball.Shape.Extent.Y) {
                            block.Hit(blocks);
                            ball.Shape.AsDynamicShape().ChangeDirection(new Vec2F (
                                ball.Shape.AsDynamicShape().Direction.X, 
                                ball.Shape.AsDynamicShape().Direction.Y * -1.00f));
                        } else {
                            block.Hit(blocks);
                            ball.Shape.AsDynamicShape().ChangeDirection(new Vec2F (
                                ball.Shape.AsDynamicShape().Direction.X * -1.00f,
                                ball.Shape.AsDynamicShape().Direction.Y));
                        }
                    }
                    if (block.IsDeleted() && block is not PowerUpBlock) {
                        values.UpdateScore(); 
                    }
                    if (block.IsDeleted() && block is PowerUpBlock) {
                        values.UpdateScore();
                        foreach (PowerUp powerUp in powerUps){
                            if (Math.Round(powerUp.Shape.Position.Y, 2) == Math.Round(block.Shape.Position.Y,2)
                            && Math.Round(powerUp.Shape.Position.X, 2) == Math.Round(block.Shape.Position.X,2)) {
                                powerUp.IsActive = true;
                                break;
                            }
                        }
                    }              
                });
            });
        }
    }
}