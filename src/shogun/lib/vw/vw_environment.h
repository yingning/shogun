/*
 * Copyright (c) 2009 Yahoo! Inc.  All rights reserved.  The copyrights
 * embodied in the content of this file are licensed under the BSD
 * (revised) open source license.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2011 Shashwat Lal Das
 * Copyright (C) 2011 Berlin Institute of Technology and Max-Planck-Society.
 */

#ifndef _VW_ENV_H__
#define _VW_ENV_H__

#include <shogun/lib/common.h>
#include <shogun/lib/v_array.h>

#include <string>
#include <vector>

namespace shogun
{

using std::string;

/** @brief Class VwEnvironment is the environment used by VW.
 *
 * Contains global constants and settings which change the behaviour
 * of Vowpal Wabbit.
 *
 * It is used while parsing input, and also while learning.
 *
 * One VwEnvironment object should be bound to the CStreamingVwFile or
 * CStreamingVwCacheFile, and the pointer to it propagated upwards
 * to CStreamingVwFeatures and finally to CVowpalWabbit.
 */
class VwEnvironment
{
public:
	/**
	 * Default constructor
	 * Should initialize with reasonable default values
	 */
	VwEnvironment();

	/**
	 * Destructor
	 */
	~VwEnvironment() { }

	/**
	 * Set number of bits used for the weight vector
	 * @param bits number of bits
	 */
	inline void set_num_bits(size_t bits) { num_bits = bits; }

	/**
	 * Return number of bits used for weight vector
	 * @return number of bits
	 */
	inline size_t get_num_bits() { return num_bits; }

	/**
	 * Set mask used while accessing features
	 * @param m mask
	 */
	inline void set_mask(size_t m) { mask = m; }

	/**
	 * Return the mask used
	 * @return mask
	 */
	inline size_t get_mask() { return mask; }

	/**
	 * Return minimum label encountered
	 * @return min label
	 */
	inline double get_min_label() { return min_label; }

	/**
	 * Return maximum label encountered
	 * @return max label
	 */
	inline double get_max_label() { return max_label; }

	/**
	 * Return number of threads used for learning
	 * @return number of threads
	 */
	inline size_t num_threads() { return 1 << thread_bits; }

	/**
	 * Return length of weight vector
	 * @return length of weight vector
	 */
	inline size_t length() { return 1 << num_bits; }

private:
	/**
	 * Initialize to default values
	 */
	void init();

public:
	/// log_2 of the number of features
	size_t num_bits;
	/// log_2 of the number of threads
	size_t thread_bits;
	/// Mask used for hashing
	size_t mask;
	/// Mask used by regressor for learning
	size_t thread_mask;
	/// Number of elements in weight vector per feature
	size_t stride;

	/// Smallest label seen
	double min_label;
	/// Largest label seen
	double max_label;

	/// Learning rate
	float eta;
	/// Decay rate of eta per pass
	float eta_decay_rate;

	/// Whether adaptive learning is used
	bool adaptive;
	/// Level of L1 regularization
	float l1_regularization;

	/// Whether to use random weights
	bool random_weights;
	/// Initial value of all elements in weight vector
	float initial_weight;

	/// Sum of updates
	float update_sum;

	/// Value of t
	float t;
	/// Initial value of t
	double initial_t;
	/// t power value while updating
	float power_t;

	/// Example number
	long long int example_number;
	/// Weighted examples
	double weighted_examples;
	/// Weighted unlabelled examples
	double weighted_unlabeled_examples;
	/// Weighted labels
	double weighted_labels;
	/// Total number of features
	size_t total_features;
	/// Sum of losses
	double sum_loss;
	/// Number of passes complete
	size_t passes_complete;

	/// Whether some namespaces are ignored
	bool ignore_some;
	/// Which namespaces to ignore
	bool ignore[256];

	/// Pairs of features to cross for quadratic updates
	std::vector<string> pairs;
};

}
#endif // _VW_ENV_H__
