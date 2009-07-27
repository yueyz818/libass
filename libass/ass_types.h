/*
 * Copyright (C) 2006 Evgeniy Stepanov <eugeni.stepanov@gmail.com>
 *
 * This file is part of libass.
 *
 * libass is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libass is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with libass; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef LIBASS_TYPES_H
#define LIBASS_TYPES_H

#include <stdint.h>

#define VALIGN_SUB 0
#define VALIGN_CENTER 8
#define VALIGN_TOP 4
#define HALIGN_LEFT 1
#define HALIGN_CENTER 2
#define HALIGN_RIGHT 3

/* Opaque objects internally used by libass.  Contents are private. */
typedef struct ass_renderer ass_renderer_t;
typedef struct render_priv render_priv_t;
typedef struct parser_priv parser_priv_t;
typedef struct ass_library ass_library_t;

/* ASS Style: line */
typedef struct {
    char *Name;
    char *FontName;
    double FontSize;
    uint32_t PrimaryColour;
    uint32_t SecondaryColour;
    uint32_t OutlineColour;
    uint32_t BackColour;
    int Bold;
    int Italic;
    int Underline;
    int StrikeOut;
    double ScaleX;
    double ScaleY;
    double Spacing;
    int Angle;
    int BorderStyle;
    double Outline;
    double Shadow;
    int Alignment;
    int MarginL;
    int MarginR;
    int MarginV;
    int Encoding;
    int treat_fontname_as_pattern;
} ass_style_t;

/*
 * ass_event_t corresponds to a single Dialogue line;
 * text is stored as-is, style overrides will be parsed later.
 */
typedef struct {
    long long Start;            // ms
    long long Duration;         // ms

    int ReadOrder;
    int Layer;
    int Style;
    char *Name;
    int MarginL;
    int MarginR;
    int MarginV;
    char *Effect;
    char *Text;

    render_priv_t *render_priv;
} ass_event_t;

/*
 * ass track represent either an external script or a matroska subtitle stream
 * (no real difference between them); it can be used in rendering after the
 * headers are parsed (i.e. events format line read).
 */
typedef struct {
    int n_styles;           // amount used
    int max_styles;         // amount allocated
    int n_events;
    int max_events;
    ass_style_t *styles;    // array of styles, max_styles length, n_styles used
    ass_event_t *events;    // the same as styles

    char *style_format;     // style format line (everything after "Format: ")
    char *event_format;     // event format line

    enum {
        TRACK_TYPE_UNKNOWN = 0,
        TRACK_TYPE_ASS,
        TRACK_TYPE_SSA
    } track_type;

    // Script header fields
    int PlayResX;
    int PlayResY;
    double Timer;
    int WrapStyle;
    char ScaledBorderAndShadow;


    int default_style;      // index of default style
    char *name;             // file name in case of external subs, 0 for streams

    ass_library_t *library;
    parser_priv_t *parser_priv;
} ass_track_t;

#endif /* LIBASS_TYPES_H */
