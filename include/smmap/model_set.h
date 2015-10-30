#ifndef model_set_h
#define model_set_h

#include <list>
#include <memory>
#include <random>

#include "smmap/deformable_model.h"

namespace smmap
{
    class ModelSet
    {
        public:
            ////////////////////////////////////////////////////////////////////
            // Constructor and destructor
            ////////////////////////////////////////////////////////////////////

            ModelSet( const GrippersDataVector& grippers_data,
                    const ObjectPointSet& object_initial_configuration );
            ~ModelSet();

            void makePredictions(
                    const std::vector< GripperTrajectory >& gripper_trajectories,
                    const ObjectPointSet& object_configuration ) const;

            void updateModels(
                    const std::vector< GripperTrajectory >& gripper_trajectories,
                    const ObjectTrajectory& object_trajectory );

            const std::vector< double >& getModelConfidence() const;

        private:
            ////////////////////////////////////////////////////////////////////
            // Private helpers
            ////////////////////////////////////////////////////////////////////

            void addModel( DeformableModel::Ptr model );

            std::vector< kinematics::VectorVector6d > calculateGripperVelocities(
                    const std::vector< GripperTrajectory >& gripper_trajectories ) const;

            kinematics::VectorMatrix3Xd calculateObjectVelocities(
                    const ObjectTrajectory& object_trajectory ) const;

            void evaluateConfidence(
                    const std::vector< GripperTrajectory >& gripper_trajectories,
                    const std::vector< kinematics::VectorVector6d >& gripper_velocities,
                    const ObjectTrajectory& object_trajectory );

            // TODO: move this to *somewhere* else
            const GrippersDataVector grippers_data_;
            const ObjectPointSet object_initial_configuration_;
            std::vector< DeformableModel::Ptr > model_list_;
            std::vector< double > model_confidence_;

            std::mt19937_64 rnd_generator_;
    };
}

#endif