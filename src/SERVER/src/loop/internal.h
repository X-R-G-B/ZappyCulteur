/*
** EPITECH PROJECT, 2023
** ZappyCulteur
** File description:
** internal
*/

#ifndef INTERNAL_H_
    #define INTERNAL_H_

    #define _CL_TYPE(is_g) (is_g) ? "graphic" : "ai"
    #define _INF_MESS "INFO: client is: %s: %d\n"
    #define DEBUG_CLIENT_LOGIN(is_g, cc) _INF_MESS, _CL_TYPE(is_g), cc->id

#endif // INTERNAL_H
