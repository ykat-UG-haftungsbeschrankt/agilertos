#!/bin/bash

BASEDIR=$(dirname "$0")
pushd "$BASEDIR"

rm cfg.h

cat <<EOT > cfg.h
/*
 * Copyright (c) 2024 ykat UG (haftungsbeschraenkt) - All Rights Reserved
 *
 * Permission for non-commercial use is hereby granted,
 * free of charge, without warranty of any kind.
 */
#ifndef ZRTOS_CFG_H
#define ZRTOS_CFG_H
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file
 * 
 * Autogenerated file containing list of possible config option.
 */
EOT


grep --include=\*.{c,h} -rhEo '[A-Z0-9_]+__CFG_[A-Z0-9_]+' . \
 | sort \
 | uniq \
 | while read line; do echo "#define $line"; done \
 >> cfg.h

cat <<EOT >> cfg.h


#ifdef __cplusplus
}
#endif
#endif
EOT

popd