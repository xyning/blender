/* SPDX-FileCopyrightText: 2023 Blender Foundation
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#include "BKE_geometry_set.hh"

namespace blender::geometry {

struct RealizeInstancesOptions {
  /**
   * The default is to generate new ids for every element (when there was any id attribute in the
   * input). This avoids having a geometry that contains the same id many times.
   * When this is `true` the ids on the original geometries are kept unchanged and ids on instances
   * are ignored. Ids are zero initialized when the original geometry did not have an id.
   */
  bool keep_original_ids = false;
  /**
   * When `true` the output geometry will contain all the generic attributes that existed on
   * instances. Otherwise, instance attributes are ignored.
   */
  bool realize_instance_attributes = true;

  bke::AnonymousAttributePropagationInfo propagation_info;
};

/**
 * Join all instances into a single geometry component for each geometry type. For example, all
 * mesh instances (including the already realized mesh) are joined into a single mesh. The output
 * geometry set does not contain any instances. If the input did not contain any instances, it is
 * returned directly.
 *
 * The `id` attribute has special handling. If there is an id attribute on any component, the
 * output will contain an `id` attribute as well. The output id is generated by mixing/hashing ids
 * of instances and of the instanced geometry data.
 */
GeometrySet realize_instances(GeometrySet geometry_set, const RealizeInstancesOptions &options);

}  // namespace blender::geometry
