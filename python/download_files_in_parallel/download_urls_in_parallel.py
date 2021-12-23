# doesn't work if pasted into python shell

import multiprocessing
import wget
import os
# Circumvent SSL: CERTIFICATE_VERIFY_FAILED errors
# https://stackoverflow.com/questions/50236117/scraping-ssl-certificate-verify-failed-error-for-http-en-wikipedia-org
import ssl
ssl._create_default_https_context = ssl._create_unverified_context

# How to get image urls
# ------------------------------
# Go to google images and use the following javascript
# urls = Array.from(document.querySelectorAll('.rg_di .rg_meta')).map(el=>JSON.parse(el.textContent).ou);
# window.open('data:text/csv;charset=utf-8,' + escape(urls.join('\n')));


def download_url(args):
    url = args[0]
    output_dir = args[1]
    try:
        wget.download(url, out=output_dir, bar=None)
        return ('Downloaded', url)
    except Exception as e:
        return (str(e), url )

def download_urls_in_parallel(args):
    
    with multiprocessing.Pool(10) as pool:
        # imap_unordered allows for results to be returned in the order in which they are generated
        for result in pool.imap_unordered(download_url, args):
            print(' '.join(result))


if __name__ == '__main__':

    output_dir = "Downloads"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    args = [
        [ "https://upload.wikimedia.org/wikipedia/commons/4/4b/Ursidae-01.jpg" , output_dir ], 
        [ "https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/2010-kodiak-bear-1.jpg/1200px-2010-kodiak-bear-1.jpg" , output_dir ], 
        [ "https://media.4-paws.org/8/a/a/0/8aa007ca1ea6b56e152eaa378cac580af6fcbdc1/YAR_6487-5272x3648.jpg" , output_dir ], 
        [ "https://image.pbs.org/video-assets/ae5wgeQ-asset-mezzanine-16x9-MqD4B29.jpg" , output_dir ], 
        [ "https://www.sciencenewsforstudents.org/wp-content/uploads/2021/04/1440_bb_brown_black_bear_explainer_feat-1030x580.jpg" , output_dir ], 
        [ "https://static.ffx.io/images/$zoom_0.6119%2C$multiply_0.7554%2C$ratio_1.777778%2C$width_1059%2C$x_0%2C$y_108/t_crop_custom/q_86%2Cf_auto/9ec3f0163d8da2ccee5a45029892d63542fbc049" , output_dir ], 
        [ "https://i.natgeofe.com/n/04fcf985-fc13-4dd3-ac21-03ad540915c1/0000016c-25c4-d982-a7ff-fdf7352c0000.jpg?w=636&h=358" , output_dir ], 
        [ "https://images.immediate.co.uk/production/volatile/sites/23/2019/10/shutterstock_1318940468-d60b405.jpg?quality=90&resize=768%2C574" , output_dir ], 
        [ "https://i.guim.co.uk/img/media/86c3481516dce247943ac2978b4f48d16a3ac265/0_170_5120_3074/master/5120.jpg?width=1200&height=1200&quality=85&auto=format&fit=crop&s=637dc5731d52754675ef36344a6af3c8" , output_dir ], 
        [ "https://cdn.mos.cms.futurecdn.net/kzRV83JTEW5HRr62rH7Ca4.jpg" , output_dir ], 
        [ "https://i.natgeofe.com/n/32211050-a89e-4b3d-9efc-2dc912b02daf/bears-01.jpg?w=636&h=422" , output_dir ], 
        [ "https://natureconservancy-h.assetsadobe.com/is/image/content/dam/tnc/nature/en/photos/tnc_52026265.jpg?crop=0,0,4000,2200&wid=4000&hei=2200&scl=1.0" , output_dir ], 
        [ "https://cdn.theatlantic.com/thumbor/WJelbTMT1SF9rDw42dOxdGlQekc=/0x207:3500x2176/960x540/media/img/mt/2017/04/RTSU94J/original.jpg" , output_dir ], 
        [ "https://media-cldnry.s-nbcnews.com/image/upload/t_fit-1500w,f_auto,q_auto:best/newscms/2019_49/3133076/191204-polar-bear-t-34-spray-paint-se-215p.jpg" , output_dir ], 
        [ "https://images.theconversation.com/files/175247/original/file-20170622-26496-7ff7v5.jpg?ixlib=rb-1.1.0&q=45&auto=format&w=1200&h=900.0&fit=crop" , output_dir ], 
        [ "https://lumiere-a.akamaihd.net/v1/images/hb_bears_mobile_19090_4f570c4d.jpeg?region=0,0,640,480" , output_dir ], 
        [ "https://helios-i.mashable.com/imagery/articles/014AwBUGZ7KwaccykFraziE/hero-image.fill.size_1248x702.v1627760709.png" , output_dir ], 
        [ "https://ichef.bbci.co.uk/news/976/cpsprodpb/12A85/production/_119312467_gettyimages-1150480683-1.jpg" , output_dir ], 
        [ "https://cdn.britannica.com/41/156441-050-A4424AEC/Grizzly-bear-Jasper-National-Park-Canada-Alberta.jpg" , output_dir ], 
        [ "https://i.natgeofe.com/n/6f8dbce3-f729-4eaf-a912-74dbd519a453/grizzly-bear_thumb_16x9.JPG?w=1200" , output_dir ], 
        [ "https://bearswire.usatoday.com/wp-content/uploads/sites/63/2021/07/3fd57f241fc14dcfb1b5c853476df956.jpg?w=1000&h=600&crop=1" , output_dir ], 
        [ "https://images.theconversation.com/files/386433/original/file-20210225-23-4pg6wh.jpg?ixlib=rb-1.1.0&rect=22%2C231%2C2107%2C1052&q=45&auto=format&w=668&h=324&fit=crop" , output_dir ], 
        [ "https://www.nwf.org/-/media/NEW-WEBSITE/Shared-Folder/Wildlife/Mammals/mammal_grizzy-bear_600x300.ashx" , output_dir ], 
        [ "https://www.exodustravels.com/sites/exod/files/styles/exo_1600_900/public/hero-image/hero-image/images/33808_hero.jpg?t=1KFtWi&itok=f-HS6516" , output_dir ], 
        [ "https://imagesvc.meredithcorp.io/v3/mm/image?url=https%3A%2F%2Fstatic.onecms.io%2Fwp-content%2Fuploads%2Fsites%2F20%2F2019%2F09%2Fgrizzly-bear.jpg&q=85" , output_dir ], 
        [ "https://c.files.bbci.co.uk/17D08/production/_119544579_gettyimages-982784476.jpg" , output_dir ], 
        [ "https://i.guim.co.uk/img/media/cf2d940296540ac41e7dfe6d3b49ba4d40b18878/0_72_2165_1299/master/2165.jpg?width=1200&height=900&quality=85&auto=format&fit=crop&s=e253604b68e655c3ce5567cfbd026107" , output_dir ], 
        [ "https://media.4-paws.org/4/1/f/7/41f7dbbe3a3116c814ec7cc633a252fd42a6b31d/VIER%20PFOTEN_2018-01-12_056-2497x1728.jpg" , output_dir ], 
        [ "https://images.newscientist.com/wp-content/uploads/2017/04/26173712/gettyimages-613093404.jpg?width=600" , output_dir ], 
        [ "https://cdn.vox-cdn.com/thumbor/6W38CjJH07s5KXCJmdMqVrdwiwk=/0x0:4690x3327/1200x800/filters:focal(1970x1289:2720x2039)/cdn.vox-cdn.com/uploads/chorus_image/image/67558200/1140444237.jpg.0.jpg" , output_dir ], 
        [ "https://www.scienceworld.ca/wp-content/uploads/iStock-1224723828-scaled-e1602089830915.jpg" , output_dir ], 
        [ "http://cdn.cnn.com/cnnnext/dam/assets/201209133725-20201209-australia-drop-bear.jpg" , output_dir ], 
        [ "https://images.theconversation.com/files/185761/original/file-20170913-3814-hmmsv9.jpg?ixlib=rb-1.1.0&rect=198%2C83%2C3273%2C2696&q=45&auto=format&w=496&fit=clip" , output_dir ], 
        [ "https://www.nps.gov/articles/images/Image-w-cred-cap_-1200w-_-Brown-Bear-page_-brown-bear-in-fog_2_1.jpg?maxwidth=1200&maxheight=1200&autorotate=false" , output_dir ], 
        [ "https://www.worldanimalprotection.org.au/sites/default/files/styles/1200x630/public/media/Two_bears_at_Romania_bear_sanctuary.jpg?itok=YkIhPRMD" , output_dir ], 
        [ "https://discovery.sndimg.com/content/dam/images/discovery/fullset/2019/9/26/grizzlyhieghts.JPG.rend.hgtvcom.406.406.suffix/1569546820894.jpeg" , output_dir ], 
        [ "https://cdn.mos.cms.futurecdn.net/nph9EKpWQdqNStmFtBWHRL.jpg" , output_dir ], 
        [ "https://static01.nyt.com/images/2019/11/12/science/00HIBERNATION1/00HIBERNATION1-videoSixteenByNineJumbo1600.jpg" , output_dir ], 
        [ "https://thumbor.forbes.com/thumbor/960x0/https%3A%2F%2Fspecials-images.forbesimg.com%2Fdam%2Fimageserve%2F1087148910%2F960x0.jpg%3Ffit%3Dscale" , output_dir ], 
        [ "https://assets.cambridge.org/97811084/83520/large_cover/9781108483520i.jpg" , output_dir ], 
        [ "https://api.timeforkids.com/wp-content/uploads/2019/11/111519_K1Bears.png" , output_dir ], 
        [ "https://s3-assets.eastidahonews.com/wp-content/uploads/2020/08/08133031/grizzly-bear.jpg" , output_dir ], 
        [ "https://cdn.shopify.com/s/files/1/0015/8135/0959/files/Free_the_Bears_Vertlogo_No_background_transparent_699x.png?v=1574998310" , output_dir ], 
        [ "https://d.newsweek.com/en/full/1855390/grizzly-bear.jpg?w=1600&h=1200&q=88&f=61efe7c833e73c61510b1fd5724d1e3f" , output_dir ], 
        [ "https://i.guim.co.uk/img/media/bd0ae53a32f1d444fcf2a51181a7c895af2d012e/0_119_5184_3110/master/5184.jpg?width=1200&height=1200&quality=85&auto=format&fit=crop&s=aba53ba9ba4175cf9cb51887b1f41ebc" , output_dir ], 
        [ "https://media.newyorker.com/photos/59096dc76552fa0be683002b/master/pass/Rathbone-What-to-Do-If-You-See-a-Bear.jpg" , output_dir ], 
        [ "https://www.vitalground.org/wp-content/uploads/2021/06/i-362880_griz_cubs.jpg" , output_dir ], 
        [ "https://blog.humanesociety.org/wp-content/uploads/2021/03/399-e1614896765776.jpg" , output_dir ], 
        [ "https://arc-anglerfish-washpost-prod-washpost.s3.amazonaws.com/public/BVTA6DXKD4I6XIV2HPRR2NESLA.jpg" , output_dir ], 
        [ "https://polarbearsinternational.org/media/3455/ct_110915-23-polar-bear-walking.jpg" , output_dir ], 
        [ "https://cdn.vox-cdn.com/thumbor/BCBVzEUkzEcRfS_4V6ODwdEuBdA=/1400x1400/filters:format(jpeg)/cdn.vox-cdn.com/uploads/chorus_asset/file/19612659/1189808891.jpg.jpg" , output_dir ], 
        [ "https://media.4-paws.org/f/2/b/3/f2b3fc4201b0d45fcc8398cdd81298a47636a830/VIER%20PFOTEN_2013-06-14_062-3860x2670-1920x1328.jpg" , output_dir ], 
        [ "https://s3-assets.eastidahonews.com/wp-content/uploads/2021/07/24174746/grizzly-bear_schiess.jpg" , output_dir ], 
        [ "https://i.natgeofe.com/n/16dba9f3-5d05-4d82-8d5f-24f594cba8df/bears-thumbnail_10_16x9.jpg?w=1200" , output_dir ], 
        [ "https://www.hakaimagazine.com/wp-content/uploads/header-polar-bear-stress.jpg" , output_dir ], 
        [ "https://images.immediate.co.uk/production/volatile/sites/23/2014/08/GettyImages-635725340-33bbe2e.jpg?quality=45&resize=768,574" , output_dir ], 
        [ "https://cdn.cnn.com/cnnnext/dam/assets/210522083131-restricted-bears-zoo-enclosure-escape-scli-intl-super-169.jpg" , output_dir ], 
        [ "https://www.fws.gov/mountain-prairie/es/images/mammals/grizzlyfeature_t.jpg" , output_dir ], 
        [ "https://cdn.vox-cdn.com/thumbor/DWQxaz-hLnp1fgrjVWDRnD4dwSY=/0x0:1460x1830/1400x1050/filters:focal(712x597:944x829):no_upscale()/cdn.vox-cdn.com/uploads/chorus_image/image/69554088/merlin_2774706.0.jpg" , output_dir ], 
        [ "https://i.ytimg.com/vi/a6gHj0bHmg8/maxresdefault.jpg" , output_dir ], 
        [ "https://thumbs-prod.si-cdn.com/QmH6-PQawF6XmQzc-edjGZHcL0o=/fit-in/1600x0/https://public-media.si-cdn.com/filer/92/43/92433590-617f-4e6c-a798-7458fae2843c/2020_nov11_grizzlybearai.jpg" , output_dir ], 
        [ "https://image.sciencenordic.com/1442991.jpg?imageId=1442991&panow=0&panoh=0&panox=0&panoy=0&heightw=0&heighth=0&heightx=0&heighty=0&width=1200&height=630" , output_dir ], 
        [ "https://files.worldwildlife.org/wwfcmsprod/images/Polar_bear_on_ice_in_Svalbard_Norway_WW294883/hero_small/85px6g3dhv_Polar_bear_on_ice_in_Svalbard_Norway_WW294883.jpg" , output_dir ], 
        [ "https://www.oysterworldwide.com/panel/wp-content/uploads/2014/02/Project_Romania_Bear_in_woods.jpg" , output_dir ], 
        [ "https://www.sciencenewsforstudents.org/wp-content/uploads/2021/04/1440_bb_spirit_bear_feat.jpg" , output_dir ], 
        [ "https://ftw.usatoday.com/wp-content/uploads/sites/90/2021/08/brown-bear.jpeg" , output_dir ], 
        [ "https://ca-times.brightspotcdn.com/dims4/default/9c106c9/2147483647/strip/true/crop/2549x1699+0+0/resize/1486x990!/quality/90/?url=https%3A%2F%2Fcalifornia-times-brightspot.s3.amazonaws.com%2F26%2F6f%2Fdcbe538c174cb97edf3eff04e6c2%2F9b0c3e37b3b54ae99fa47ea338d57911" , output_dir ], 
        [ "https://i.guim.co.uk/img/media/d48833169561357e8351ac0bb01e61e17ca18326/0_189_5661_3397/master/5661.jpg?width=1200&height=1200&quality=85&auto=format&fit=crop&s=93dc1fb6694a0c594b39d17e08da28af" , output_dir ], 
        [ "http://www.bearsmart.com/wp-content/uploads/2015/01/masthead-gb-family2.jpg" , output_dir ], 
        [ "https://www.sciencemag.org/sites/default/files/styles/inline__450w__no_aspect/public/bears_16x9.jpg?itok=iXdtax2M" , output_dir ], 
        [ "https://polarbearsinternational.org/media/3647/kt-miller_6846.jpg" , output_dir ], 
        [ "https://www.treehugger.com/thmb/DCJOq0rnY9khPLLrrUhKLxW8Uj4=/1414x1414/smart/filters:no_upscale()/bear.primary-60c0a7156ff742758befc25769168b6a.jpg" , output_dir ], 
        [ "https://bloximages.chicago2.vip.townnews.com/missoulian.com/content/tncms/assets/v3/editorial/d/9e/d9ee4128-90df-5d8f-8004-5e977e074321/60932c999b530.image.jpg?resize=1200%2C852" , output_dir ], 
        [ "https://ewscripps.brightspotcdn.com/4b/69/177e18944d54b6ee73f9e34aeeda/generic-1280-4.png" , output_dir ], 
        [ "https://static.scientificamerican.com/sciam/cache/file/EFD4FD4C-C22F-4370-B66EFBAD8D47DC45_source.jpg?w=590&h=800&4FEBBE5E-5259-4B10-9B4645DA6F6FFFFC" , output_dir ], 
        [ "http://www.bearsmart.com/wp-content/uploads/2015/01/bear-look.jpg" , output_dir ], 
        [ "https://upload.wikimedia.org/wikipedia/commons/f/f6/Ursus_arctos_californicus%2C_Santa_Barbara%2C_Natural_History_Museum.jpg" , output_dir ], 
        [ "https://thumbs-prod.si-cdn.com/NReBszLvUf5vT9tjXOhbNIFnrOw=/fit-in/1600x0/https://public-media.si-cdn.com/filer/0e/fd/0efd4a8c-5f43-4e75-adbe-843c8f599ee2/sep2015_d01_kermodebears.jpg" , output_dir ], 
        [ "https://www.history.com/.image/ar_4:3%2Cc_fill%2Ccs_srgb%2Cfl_progressive%2Cq_auto:good%2Cw_1200/MTU3ODc4NjAyNzE5MjQxNTQ1/gettyimages-10182954-2.jpg" , output_dir ], 
        [ "https://www.hakaimagazine.com/wp-content/uploads/header-salmon-parasites.jpg" , output_dir ], 
        [ "https://static01.nyt.com/images/2020/11/24/science/11SCI-AI-BEARS/11SCI-AI-BEARS-mediumSquareAt3X.jpg" , output_dir ], 
        [ "https://lumiere-a.akamaihd.net/v1/images/p_bears_19090_1f076ac4.jpeg" , output_dir ], 
        [ "https://www.eurekalert.org/multimedia/pub/web/220589_web.jpg" , output_dir ], 
        [ "http://bearwithus.org/wp-content/uploads/2012/09/bear-brown-guy-June-2007.jpg" , output_dir ], 
        [ "https://upload.wikimedia.org/wikipedia/commons/thumb/e/eb/Sun-bear.jpg/1200px-Sun-bear.jpg" , output_dir ], 
        [ "https://www.pbs.org/wnet/nature/files/2009/09/Untitled-1-1280x720.png" , output_dir ], 
        [ "https://assets.teenvogue.com/photos/60b798340a5b6e53c9c0c78b/2:3/w_1693,h_2540,c_limit/GettyImages-89668310.jpg" , output_dir ], 
        [ "https://media.hswstatic.com/eyJidWNrZXQiOiJjb250ZW50Lmhzd3N0YXRpYy5jb20iLCJrZXkiOiJnaWZcL0Jyb3duLWJlYXIuanBnIiwiZWRpdHMiOnsicmVzaXplIjp7IndpZHRoIjo4Mjh9fX0=" , output_dir ], 
        [ "https://ichef.bbci.co.uk/images/ic/976xn/p07shq3q.jpg" , output_dir ], 
        [ "http://bearwithus.org/wp-content/uploads/2012/09/Cahrlie-Russell-aBiscuit-.jpg" , output_dir ], 
        [ "https://www.ikea.com/au/en/images/products/djungelskog-soft-toy-brown-bear__0877178_pe662336_s5.jpg" , output_dir ], 
        [ "https://i.guim.co.uk/img/media/11d4c182d094199e26ddb36febe67123a9bbc93a/34_246_2966_4275/master/2966.jpg?width=700&quality=85&auto=format&fit=max&s=e78fc63cf43a4a9830619c324b5c854b" , output_dir ], 
        [ "http://www.xinhuanet.com/english/2021-07/11/1310054955_16259932487891n.jpg" , output_dir ], 
        [ "https://dkt6rvnu67rqj.cloudfront.net/cdn/ff/DqiY7B-jC3CZFdc55wvrBx3wzN9pJqCY-BhU1IJK03A/1579912958/public/styles/600x400/public/media/au_files/1021226.jpg?itok=P3PeP3RE" , output_dir ], 
        [ "https://cdn.vox-cdn.com/thumbor/pKdHKTdx7AWf5wF2xIaTRnF7OIs=/0x0:6159x4106/1200x800/filters:focal(2588x1561:3572x2545)/cdn.vox-cdn.com/uploads/chorus_image/image/65416102/48839836861_4e06fcc663_o.0.jpg" , output_dir ], 
        [ "https://cdn.wionews.com/sites/default/files/styles/story_page/public/2021/07/18/202825-untitled-design-2021-07-18t195111787.jpg" , output_dir ], 
        [ "https://cdn.vox-cdn.com/thumbor/poOTNEb3EQ99KjZzlus8ZsLBFZQ=/1400x1050/filters:format(jpeg)/cdn.vox-cdn.com/uploads/chorus_asset/file/22138089/1197059301.jpg" , output_dir ], 
        [ "https://upload.wikimedia.org/wikipedia/commons/7/7f/European_Brown_Bear.jpg" , output_dir ], 
        [ "https://cdn.tsln.com/wp-content/uploads/sites/13/2018/10/bears-tsln-101318-1240x823.jpg" , output_dir ], 
        [ "https://i.insider.com/60f211c471757b0018c6a379?width=1136&format=jpeg" , output_dir ], 
    ]

    download_urls_in_parallel(args)


