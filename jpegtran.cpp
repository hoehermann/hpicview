#include "jpegtran.h"

#include <cdjpeg.h>
extern "C" { // TODO: this looks hackish. how to do this properly? force g++ for all files?
#include <transupp.h>
}
#include <stdexcept>

std::string transform(std::string input, JXFORM_CODE transform) {
    struct jpeg_decompress_struct srcinfo;
    struct jpeg_compress_struct dstinfo;
    struct jpeg_error_mgr jsrcerr, jdsterr;
    //struct cdjpeg_progress_mgr progress;
    jvirt_barray_ptr * src_coef_arrays;
    jvirt_barray_ptr * dst_coef_arrays;
    jpeg_transform_info transformoption; /* image transformation options */
    /* Initialize the JPEG decompression object with default error handling. */
    srcinfo.err = jpeg_std_error(&jsrcerr);
    jpeg_create_decompress(&srcinfo);
    /* Initialize the JPEG compression object with default error handling. */
    dstinfo.err = jpeg_std_error(&jdsterr);
    jpeg_create_compress(&dstinfo);
    /* from parse_switches() and static declarations */
    /* Set up default JPEG parameters. */
    JCOPY_OPTION copyoption = JCOPYOPT_ALL;
    transformoption.transform = JXFORM_NONE;
    transformoption.perfect = TRUE;
    transformoption.trim = FALSE;
    transformoption.force_grayscale = FALSE;
    transformoption.crop = FALSE;
    jsrcerr.trace_level = jdsterr.trace_level;
    srcinfo.mem->max_memory_to_use = dstinfo.mem->max_memory_to_use;
    // start_progress_monitor((j_common_ptr) &dstinfo, &progress);
    /* Specify data source for decompression */
    jpeg_mem_src(&srcinfo, (unsigned char *)input.c_str(), input.size()); /* read from memory*/
    /* Enable saving of extra markers that we want to copy */
    jcopy_markers_setup(&srcinfo, copyoption);
    /* Read file header */
    (void) jpeg_read_header(&srcinfo, TRUE);
    /* from select_transform() */
    transformoption.transform = transform;
    if (!jtransform_request_workspace(&srcinfo, &transformoption)) {
        throw std::runtime_error("transformation is not perfect");
    }
    /* Read source file as DCT coefficients */
    src_coef_arrays = jpeg_read_coefficients(&srcinfo);
    /* Initialize destination compression parameters from source values */
    jpeg_copy_critical_parameters(&srcinfo, &dstinfo);
    /* Adjust destination parameters if required by transform options;
    * also find out which set of coefficient arrays will hold the output.
    */
    dst_coef_arrays = jtransform_adjust_parameters(
        &srcinfo, &dstinfo,src_coef_arrays,&transformoption
    );
    /* Specify data destination for compression */
    unsigned char * outbuffer = NULL;
    unsigned long outsize = 0;
    jpeg_mem_dest (&dstinfo, &outbuffer, &outsize); /* store in memory */
    /* Start compressor (note no image data is actually written here) */
    jpeg_write_coefficients(&dstinfo, dst_coef_arrays);
    /* Copy to the output file any extra markers that we want to preserve */
    jcopy_markers_execute(&srcinfo, &dstinfo, copyoption);
    /* Execute image transformation, if any */
    jtransform_execute_transformation(
        &srcinfo, &dstinfo,src_coef_arrays,&transformoption
    );
    /* Finish compression and release memory */
    jpeg_finish_compress(&dstinfo);
    jpeg_destroy_compress(&dstinfo);
    (void) jpeg_finish_decompress(&srcinfo);
    jpeg_destroy_decompress(&srcinfo);
    //end_progress_monitor((j_common_ptr) &dstinfo);
    if(jsrcerr.num_warnings + jdsterr.num_warnings) {
        throw std::runtime_error("libjpeg warnings occurred");
    }
    std::string output((char *)outbuffer, outsize);
    free(outbuffer);
    return output;
}

JPEGtran::JPEGtran()
{
    //ctor
}

std::string JPEGtran::rotate_left(std::string input) {
    return transform(input, JXFORM_ROT_270);
}

std::string JPEGtran::rotate_right(std::string input) {
    return transform(input, JXFORM_ROT_90);

}


JPEGtran::~JPEGtran() {
    //dtor
}
