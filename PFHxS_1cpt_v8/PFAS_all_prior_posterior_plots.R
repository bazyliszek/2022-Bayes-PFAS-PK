## Create multipart figures of priors and posteriors
library(ggplot2)
library(ggpubr)
library(here)
sa <- "Cbgd-80_"

## Half-life, Volume of distribution, Clearance

# Run from PFHxS directory
pfasheredir <- c(rep(here("../"),4))
pfas <- c("PFOA","PFOS","PFNA","PFHxS")
pfasoutdir <- paste0(pfasheredir,pfas,"_1cpt_v8/output-plots/")
dir.exists(pfasoutdir)

parms <- c("hl","vd","CL") 

for (parmnow in parms) {
  pgmlist <- list()
  pgsdlist <- list()
  for (j in 1:4) {
    pfasnow <- pfas[j]
    load(paste0( pfasoutdir[j], sa, pfasnow,"_",parmnow,"_gm.RData"))
    pgmlist[[j]] <- p + guides(linetype = guide_legend(override.aes = list(size = 0.75)))
    load(paste0( pfasoutdir[j], sa, pfasnow,"_",parmnow,"_gsd.RData"))
    pgsdlist[[j]] <- p + guides(linetype = guide_legend(override.aes = list(size = 0.75)))
  }
  pall <- ggarrange(plotlist = list(pgmlist[[1]],pgsdlist[[1]],
                                 pgmlist[[2]],pgsdlist[[2]],
                                 pgmlist[[3]],pgsdlist[[3]],
                                 pgmlist[[4]],pgsdlist[[4]]),ncol=2,nrow=4)
  # print(pall)
  ggsave(filename = file.path(pfasoutdir[[4]],
                              paste0("Fig_",parmnow,".pdf")),
         plot = pall,height = 8,width=6.5,dpi = 600,scale=1.25)
}

## DWC below MRL
plist <- list()
parmnow<-"DWC_below_MRL"
for (j in c(1,3,4)) {
  pfasnow <- pfas[j]
  load(paste0( pfasoutdir[j], sa, pfasnow,"_",parmnow,".RData"))
  plist <- append(plist,list(p))
  
}
pallDWC <- ggarrange(plotlist = plist,ncol=1,nrow=3)
# print(pallDWC)
ggsave(filename = file.path(pfasoutdir[[4]],
                            paste0("Fig_",parmnow,".pdf")),
       plot = pallDWC,height = 8,width=6.5,dpi = 600,scale=1.25)

