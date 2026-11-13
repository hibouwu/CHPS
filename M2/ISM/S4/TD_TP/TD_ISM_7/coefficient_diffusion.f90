      program coefficient_diffusion  
      implicit double precision (a-h,o-z)
      integer, parameter :: stdout=6,MAXLENGTH=1000000 
      character*5 :: tab_data(1:9)
      character*120 :: donnee
      integer, dimension (:), allocatable :: ntaille
      integer, dimension (:,:), allocatable :: ndata
      real*8, dimension (:,:), allocatable :: x,y,z
      real*8, dimension (:), allocatable :: ecart_distance,ecart_type

! Initialisation

      allocate (x(1:MAXLENGTH,1:9))
      allocate (y(1:MAXLENGTH,1:9))
      allocate (z(1:MAXLENGTH,1:9))

      allocate (ntaille(1:9)) ; ntaille = 0

      tab_data(1) = 'data1'
      tab_data(2) = 'data2'
      tab_data(3) = 'data3'
      tab_data(4) = 'data4'
      tab_data(5) = 'data5'
      tab_data(6) = 'data6'
      tab_data(7) = 'data7'
      tab_data(8) = 'data8'
      tab_data(9) = 'data9'

! Lectures des data

      allocate (ndata(1:2,1:3))

      do i = 1,9
         open (1,file=tab_data(i),status='old')
         do j = 1,MAXLENGTH
            read (1,1000,end=10,err=10) donnee
            ntaille(i) = ntaille(i) + 1 
            call conversion_coordonnees(len(donnee),donnee,ndata)
            read (donnee(ndata(1,1):ndata(2,1)),*) x(j,i)
            read (donnee(ndata(1,2):ndata(2,2)),*) y(j,i)
            read (donnee(ndata(1,3):ndata(2,3)),*) z(j,i)
         end do
10       continue
      end do

      deallocate (ndata) ; close(1)

! Taille des vecteurs x/y/z

      mtaille = huge(ntaille)
      do i = 1,9
         mtaille = min(mtaille,ntaille(i))
      end do


! Parametres moyenne glissante                      

      max_particule = 1                ! compris entre 1 et 9
      max_iteration = 9000              ! compris entre 1 et 9000

      write (*,*) 'Nombre maximum de particule '
      read (*,*) max_particule
      write (*,*) 'Longueur des segments : '
      read (*,*) max_iteration

      num_segment = mtaille / max_iteration

      allocate (ecart_distance(1:max_iteration)) ; ecart_distance = 0.0d0
      allocate (ecart_type(1:max_iteration)) ; ecart_type = 0.0d0

! Moyenne glissante

      do i = 1,max_particule
         ninit = 1
         do j = 1,num_segment  
            x0 = x(ninit,i) ; y0 = y(ninit,i) ; z0 = z(ninit,i)
            do k = 1,max_iteration
               dx = x(ninit+k,i) - x0 
               dy = y(ninit+k,i) - y0 
               dz = z(ninit+k,i) - z0 
               dist2 = dx*dx + dy*dy + dz*dz
               ecart_distance(k) = ecart_distance(k) + dist2       
               ecart_type(k) = ecart_type(k) + dist2*dist2
            end do
            ninit = ninit + max_iteration
         end do
      end do

! Sortie       

      coef = 1.0d0 / real(num_segment*max_particule)    ! inverse du nombre d'éléments moyennés
      temps = 2.0d0                                     ! temps en picoseconde

      open (1,file='moyenne.data',status='unknown')

      do i = 1,max_iteration
         ecart_distance(i) = coef*ecart_distance(i)
         ecart_type(i) = coef*ecart_type(i)
      end do

      do i = 1,max_iteration
         dist2 = ecart_distance(i) 
         rmsd = sqrt(ecart_type(i) - dist2*dist2)
         write (1,2000) real(i)*temps,dist2,rmsd           
      end do

      write (*,*) 'Analysis done, closing the file moyenne.data '

      close (1)

! Formats

1000  format (a120)
2000  format (f10.2,2(4x,f16.2))

      end
!
      subroutine conversion_coordonnees(longueur_chaine,chaine,ndata)
      implicit double precision (a-h,o-z)
      character(len=1) :: blanc
      character(len=longueur_chaine) :: chaine
      dimension ndata(1:2,1:3)
      blanc = ' ' ; ndebut = 1
      do i = 1,3       
        do j = ndebut,longueur_chaine
            if (chaine(j:j) /= blanc) then
                ndata(1,i) = j
                do k = j+1,longueur_chaine
                    if (chaine(k:k) == blanc) then
                        ndebut = k ; ndata(2,i) = k - 1
                        exit
                    end if
                end do
                goto 10 
            end if
        end do
10      continue
      end do
      return
      end 
