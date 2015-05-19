/*
 * Copyright (C) 2015 Stephan Vedder <stefano.pigozzi@gmail.com>
 *
 * This file is part of libass.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "config.h"

#ifdef CONFIG_DIRECTWRITE

#include <dwrite.h>

extern "C"
{
#include "ass_directwrite.h"
}

static ASS_FontProviderFuncs directwrite_callbacks = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

ASS_FontProvider *
ass_directwrite_add_provider(ASS_Library *lib, ASS_FontSelector *selector,
                          const char *config)
{
	HRESULT hr = S_OK;
	IDWriteFactory* dwFactory = NULL;
	ASS_FontProvider *provider = NULL;

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            (IUnknown**)(&dwFactory));

	if(FAILED(hr))
	{
		goto exit;
	}	
	

    provider = ass_font_provider_new(selector, &directwrite_callbacks, dwFactory);

exit: 
    return provider;
}

#endif